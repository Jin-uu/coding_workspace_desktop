const MAX = 10000000;
const arr = new Array(MAX);
arr.push({a:22});

console.time("Array insertion time");
for (let i=0; i<arr.length; i++) {
    arr[i] = i;
}

console.timeEnd("Array insertion time")
