const MAX = 10000000;
const buffer = new ArrayBuffer(MAX*1);
const typedarr = new Int8Array(buffer);

console.time("TypedArray insertion time");
for (let i=0; i<typedarr.length; i++) {
    typedarr[i] = i;
}

console.timeEnd("TypedArray insertion time")
