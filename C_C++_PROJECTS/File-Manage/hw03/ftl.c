#define PRINT_FOR_DEBUG

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include "blkmap.h"

AddrMapTbl addrmaptbl;
extern FILE *devicefp;
int reserved_empty_blk = DATABLKS_PER_DEVICE;

/****************  prototypes ****************/
void ftl_open();
void ftl_write(int lsn, char *sectorbuf);
void ftl_read(int lsn, char *sectorbuf);
void print_block(int pbn);
void print_addrmaptbl();

//
// flash memory를 처음 사용할 때 필요한 초기화 작업, 예를 들면 address mapping table에 대한
// 초기화 등의 작업을 수행한다
//

void ftl_open()
{
	int i;

	// initialize the address mapping table
	for(i = 0; i < BLOCKS_PER_DEVICE; i++) {		// 모두 -1로 초기화
		addrmaptbl.pbn[i] = -1;
	}

	//
	// 추가적으로 필요한 작업이 있으면 수행하면 되고 없으면 안해도 무방함
	//
	return;
}

//
// file system을 위한 FTL이 제공하는 write interface
// 'sectorbuf'가 가리키는 메모리의 크기는 'SECTOR_SIZE'이며, 호출하는 쪽에서 미리 메모리를 할당받아야 함
//
void ftl_write(int lsn, char *sectorbuf) {
	//
	// block mapping 기법에서 overwrite가 발생하면 이를 해결하기 위해 반드시 하나의 empty block이
	// 필요하며, 초기값은 flash memory에서 맨 마지막 block number를 사용함
	// overwrite를 해결하고 난 후 당연히 reserved_empty_blk는 overwrite를 유발시킨 (invalid) block이 되어야 함
	// 따라서 reserved_empty_blk는 고정되어 있는 것이 아니라 상황에 따라 계속 바뀔 수 있음
	//	

	// lbn, offset, pbn, ppn 계산
	int lbn = lsn / PAGES_PER_BLOCK;
	int offset = lsn % PAGES_PER_BLOCK;
	int pbn = addrmaptbl.pbn[lbn];
	int ppn = pbn*PAGES_PER_BLOCK + offset;

	int isOverwrite;		// TRUE:OverWrite / FALSE:JustWrite
	if(pbn == -1){						// pbn이 초기값이면
		isOverwrite = FALSE;			// JustWrite
	}			
	else{								// pbn이 초기값이 아니면
		char check_isOverwrite[PAGE_SIZE];				// 페이지 버퍼
		if(dd_read(ppn, check_isOverwrite) == -1){		// 쓰려는 페이지 읽어보기
			printf("error in dd_read()\n");
			return;
		}
		if(check_isOverwrite[0] == (char)0xff){			// 읽은 페이지가 초기화상태 그대로면
		isOverwrite = FALSE;							// JustWrite
		}
		else {											// 읽은 페이지가 초기값이 아니면
			isOverwrite = TRUE;							// OverWrite
		}
	}	

	char *pagebuf;			// Write 할 페이지버퍼
	SpareData *sdata;		// 스페어 데이터
	
	pagebuf = (char *)malloc(PAGE_SIZE);	// 페이지 버퍼 메모리 할당
	strcpy(pagebuf, sectorbuf);				// 페이지 버퍼에 인자로 받은 sectorbuf 복사
	sdata = (SpareData *)malloc(SPARE_SIZE);	// 스페어 데이터
	sdata->lsn = lsn;							// lsn값 지정
	memcpy(pagebuf+SECTOR_SIZE, sdata, SPARE_SIZE);	// 페이지 버퍼 뒤에 스페어 데이터 붙이기

	if(isOverwrite){	// OverWrite
		// 1. Copy
		for(int i=0; i<PAGES_PER_BLOCK; i++){	// 해당 블록에 대해
			if(i==offset) continue;				// 덮어쓰는 칸은 복사 안함
			char *copy_pagebuf = (char*)malloc(PAGE_SIZE);			// 임시 페이지 버퍼
			if(dd_read(pbn*PAGES_PER_BLOCK+i,copy_pagebuf) == -1){	// 페이지 값 읽어와서
				printf("error in dd_read()\n");
			}
			if(dd_write(reserved_empty_blk*PAGES_PER_BLOCK+i,copy_pagebuf) == -1){		// Blank Block에 복사
				printf("error in dd_write()\n");
			}
			free(copy_pagebuf);
		}
		
		// 2. Write
		if(dd_write(reserved_empty_blk*PAGES_PER_BLOCK+offset, pagebuf) == -1){		// 원래 쓰려던 데이터 Blank Block에 복사
			return;
		}

		// 3. Erase
		if(dd_erase(pbn) == -1){													// 옮기기 전 블록 데이터 삭제
			return;
		}

		// 4. toggle MapTbl
		int temp = addrmaptbl.pbn[lbn];				// Mapping Table 값 갱신
		addrmaptbl.pbn[lbn] = reserved_empty_blk;
		reserved_empty_blk = temp;
	}
	else{						// Just Write
		pbn = lbn;				// pbn값 갱신
		ppn = pbn*PAGES_PER_BLOCK + offset;		// ppn값 갱신
		// 1. Write
		if(dd_write(ppn, pagebuf) == -1){		// 갱신된 값으로 write
			printf("error in dd_write()\n");
			return;
		}
		// 2. Set MappingTable
		addrmaptbl.pbn[lbn] = pbn;				// Mapping Table 값 갱신
	}

	// L. Free Datas		//TODO
	free(pagebuf);
	free(sdata);
	return;
}

//
// file system을 위한 FTL이 제공하는 read interface
// 'sectorbuf'가 가리키는 메모리의 크기는 'SECTOR_SIZE'이며, 호출하는 쪽에서 미리 메모리를 할당받아야 함
// 
void ftl_read(int lsn, char *sectorbuf)
{
#ifdef PRINT_FOR_DEBUG			// 필요 시 현재의 block mapping table을 출력해 볼 수 있음
	// print_addrmaptbl();
#endif
	// 1. Get lbn, offset, pbn, ppn 계산
	int lbn = lsn / PAGES_PER_BLOCK;
	int offset = lsn % PAGES_PER_BLOCK;
	int pbn = addrmaptbl.pbn[lbn];
	int ppn = pbn*PAGES_PER_BLOCK + offset;
	if(pbn == -1){				// 값이 안들어가 있는 블록이면
		printf("No Data to Read.\n");	
		return;					// return
	}

	// 2. Set pagebuffer
	char *pagebuf = (char *)malloc(PAGE_SIZE);


	// 3. Read
	if(dd_read(ppn, pagebuf) == -1){ printf("error in dd_read()\n"); return; }	// 읽어옴

	// 4. Copy to sectorbuffer
	memcpy(sectorbuf, pagebuf, SECTOR_SIZE);		// sectorbuffer에 pagebuffer 앞부분 복사

	// L. Free Datas
	free(pagebuf);
	return;
}

//
// for debugging
//
void print_block(int pbn)
{
	char *pagebuf;
	SpareData *sdata;
	int i;
	
	pagebuf = (char *)malloc(PAGE_SIZE);
	sdata = (SpareData *)malloc(SPARE_SIZE);

	printf("Physical Block Number: %d\n", pbn);

	for(i = pbn*PAGES_PER_BLOCK; i < (pbn+1)*PAGES_PER_BLOCK; i++)
	{
		dd_read(i, pagebuf);
		memcpy(sdata, pagebuf+SECTOR_SIZE, SPARE_SIZE);
		printf("\t   %5d-[%7d]\n", i, sdata->lsn);
	}

	free(pagebuf);
	free(sdata);

	return;
}

//
// for debugging
//
void print_addrmaptbl()
{
	int i;

	printf("Address Mapping Table: \n");
	for(i = 0; i < DATABLKS_PER_DEVICE; i++)
	{
		if(addrmaptbl.pbn[i] >= 0)
		{
			printf("[%d:%d]\n", i, addrmaptbl.pbn[i]);
		}

		if(i%10 == 9) printf("\n");
	}
	printf("\n");
}
