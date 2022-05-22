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
// flash memory�� ó�� ����� �� �ʿ��� �ʱ�ȭ �۾�, ���� ��� address mapping table�� ����
// �ʱ�ȭ ���� �۾��� �����Ѵ�
//

void ftl_open()
{
	int i;

	// initialize the address mapping table
	for(i = 0; i < BLOCKS_PER_DEVICE; i++) {		// ��� -1�� �ʱ�ȭ
		addrmaptbl.pbn[i] = -1;
	}

	//
	// �߰������� �ʿ��� �۾��� ������ �����ϸ� �ǰ� ������ ���ص� ������
	//
	return;
}

//
// file system�� ���� FTL�� �����ϴ� write interface
// 'sectorbuf'�� ����Ű�� �޸��� ũ��� 'SECTOR_SIZE'�̸�, ȣ���ϴ� �ʿ��� �̸� �޸𸮸� �Ҵ�޾ƾ� ��
//
void ftl_write(int lsn, char *sectorbuf) {
	//
	// block mapping ������� overwrite�� �߻��ϸ� �̸� �ذ��ϱ� ���� �ݵ�� �ϳ��� empty block��
	// �ʿ��ϸ�, �ʱⰪ�� flash memory���� �� ������ block number�� �����
	// overwrite�� �ذ��ϰ� �� �� �翬�� reserved_empty_blk�� overwrite�� ���߽�Ų (invalid) block�� �Ǿ�� ��
	// ���� reserved_empty_blk�� �����Ǿ� �ִ� ���� �ƴ϶� ��Ȳ�� ���� ��� �ٲ� �� ����
	//	

	// lbn, offset, pbn, ppn ���
	int lbn = lsn / PAGES_PER_BLOCK;
	int offset = lsn % PAGES_PER_BLOCK;
	int pbn = addrmaptbl.pbn[lbn];
	int ppn = pbn*PAGES_PER_BLOCK + offset;

	int isOverwrite;		// TRUE:OverWrite / FALSE:JustWrite
	if(pbn == -1){						// pbn�� �ʱⰪ�̸�
		isOverwrite = FALSE;			// JustWrite
	}			
	else{								// pbn�� �ʱⰪ�� �ƴϸ�
		char check_isOverwrite[PAGE_SIZE];				// ������ ����
		if(dd_read(ppn, check_isOverwrite) == -1){		// ������ ������ �о��
			printf("error in dd_read()\n");
			return;
		}
		if(check_isOverwrite[0] == (char)0xff){			// ���� �������� �ʱ�ȭ���� �״�θ�
		isOverwrite = FALSE;							// JustWrite
		}
		else {											// ���� �������� �ʱⰪ�� �ƴϸ�
			isOverwrite = TRUE;							// OverWrite
		}
	}	

	char *pagebuf;			// Write �� ����������
	SpareData *sdata;		// ����� ������
	
	pagebuf = (char *)malloc(PAGE_SIZE);	// ������ ���� �޸� �Ҵ�
	strcpy(pagebuf, sectorbuf);				// ������ ���ۿ� ���ڷ� ���� sectorbuf ����
	sdata = (SpareData *)malloc(SPARE_SIZE);	// ����� ������
	sdata->lsn = lsn;							// lsn�� ����
	memcpy(pagebuf+SECTOR_SIZE, sdata, SPARE_SIZE);	// ������ ���� �ڿ� ����� ������ ���̱�

	if(isOverwrite){	// OverWrite
		// 1. Copy
		for(int i=0; i<PAGES_PER_BLOCK; i++){	// �ش� ��Ͽ� ����
			if(i==offset) continue;				// ����� ĭ�� ���� ����
			char *copy_pagebuf = (char*)malloc(PAGE_SIZE);			// �ӽ� ������ ����
			if(dd_read(pbn*PAGES_PER_BLOCK+i,copy_pagebuf) == -1){	// ������ �� �о�ͼ�
				printf("error in dd_read()\n");
			}
			if(dd_write(reserved_empty_blk*PAGES_PER_BLOCK+i,copy_pagebuf) == -1){		// Blank Block�� ����
				printf("error in dd_write()\n");
			}
			free(copy_pagebuf);
		}
		
		// 2. Write
		if(dd_write(reserved_empty_blk*PAGES_PER_BLOCK+offset, pagebuf) == -1){		// ���� ������ ������ Blank Block�� ����
			return;
		}

		// 3. Erase
		if(dd_erase(pbn) == -1){													// �ű�� �� ��� ������ ����
			return;
		}

		// 4. toggle MapTbl
		int temp = addrmaptbl.pbn[lbn];				// Mapping Table �� ����
		addrmaptbl.pbn[lbn] = reserved_empty_blk;
		reserved_empty_blk = temp;
	}
	else{						// Just Write
		pbn = lbn;				// pbn�� ����
		ppn = pbn*PAGES_PER_BLOCK + offset;		// ppn�� ����
		// 1. Write
		if(dd_write(ppn, pagebuf) == -1){		// ���ŵ� ������ write
			printf("error in dd_write()\n");
			return;
		}
		// 2. Set MappingTable
		addrmaptbl.pbn[lbn] = pbn;				// Mapping Table �� ����
	}

	// L. Free Datas		//TODO
	free(pagebuf);
	free(sdata);
	return;
}

//
// file system�� ���� FTL�� �����ϴ� read interface
// 'sectorbuf'�� ����Ű�� �޸��� ũ��� 'SECTOR_SIZE'�̸�, ȣ���ϴ� �ʿ��� �̸� �޸𸮸� �Ҵ�޾ƾ� ��
// 
void ftl_read(int lsn, char *sectorbuf)
{
#ifdef PRINT_FOR_DEBUG			// �ʿ� �� ������ block mapping table�� ����� �� �� ����
	// print_addrmaptbl();
#endif
	// 1. Get lbn, offset, pbn, ppn ���
	int lbn = lsn / PAGES_PER_BLOCK;
	int offset = lsn % PAGES_PER_BLOCK;
	int pbn = addrmaptbl.pbn[lbn];
	int ppn = pbn*PAGES_PER_BLOCK + offset;
	if(pbn == -1){				// ���� �ȵ� �ִ� ����̸�
		printf("No Data to Read.\n");	
		return;					// return
	}

	// 2. Set pagebuffer
	char *pagebuf = (char *)malloc(PAGE_SIZE);


	// 3. Read
	if(dd_read(ppn, pagebuf) == -1){ printf("error in dd_read()\n"); return; }	// �о��

	// 4. Copy to sectorbuffer
	memcpy(sectorbuf, pagebuf, SECTOR_SIZE);		// sectorbuffer�� pagebuffer �պκ� ����

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
