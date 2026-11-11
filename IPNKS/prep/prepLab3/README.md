# IPNKS - Lab 3 prep (guess: arrays and objects)

Six exercises on arrays, objects and arrays of objects, based on AV4a (arrays), AV4b (objects) and the Arrays and Objects lectures. Same format as Lab 2: write a function that `return`s the result. No `prompt`, no `alert`.

This is a guess at the topic, based on the order of the course material.

**Testing in the Console:** arrays and objects can't be compared with `===`, so compare them as text:

```js
JSON.stringify(unique([1,2,2,3,1])) === JSON.stringify([1,2,3])  // true
```

---

## Exercise 1: `cartTotal(cart)`

Each item is `{name, price, qty}`. Return the total: `price * qty` summed over all items.

| Call | Expected |
|---|---|
| `cartTotal([{name:"pen", price:20, qty:3}, {name:"book", price:350, qty:1}])` | `410` |
| `cartTotal([{name:"x", price:99, qty:0}])` | `0` |
| `cartTotal([])` | `0` |

---

## Exercise 2: `unique(arr)`

Remove duplicates, keeping the first occurrence of each, in the original order.

| Call | Expected |
|---|---|
| `unique([1,2,2,3,1])` | `[1,2,3]` |
| `unique(["a","A","a"])` | `["a","A"]` |
| `unique([])` | `[]` |

---

## Exercise 3: `average(arr)`

Return the average of the numbers, rounded to 2 decimals, as a **number**. Return `0` for an empty array.

| Call | Expected |
|---|---|
| `average([8,9,10])` | `9` |
| `average([7,8])` | `7.5` |
| `average([10,9,9])` | `9.33` |
| `average([])` | `0` |

---

## Exercise 4: `countWords(text)`

Lowercase the text and split it into words (there can be several spaces in a row). Return an object mapping each word to how many times it appears.

| Call | Expected |
|---|---|
| `countWords("The cat and the hat")` | `{the:2, cat:1, and:1, hat:1}` |
| `countWords("  JS  js Js ")` | `{js:3}` |
| `countWords("")` | `{}` |

---

## Exercise 5: Students

The input is an array of `{name, grade}`.

- `topStudent(students)`: return the name of the student with the highest grade. If there's a tie, return the **first** one. Return `null` for an empty array.
- `passedNames(students, min)`: return the names of students with `grade >= min`, sorted alphabetically.

Test data:

```js
const st = [{name:"Ana",grade:8},{name:"Bojan",grade:10},{name:"Cvetan",grade:10},{name:"Dana",grade:6}];
```

| Call | Expected |
|---|---|
| `topStudent(st)` | `"Bojan"` |
| `topStudent([{name:"Eli",grade:5}])` | `"Eli"` |
| `topStudent([])` | `null` |
| `passedNames(st, 8)` | `["Ana","Bojan","Cvetan"]` |
| `passedNames(st, 6)` | `["Ana","Bojan","Cvetan","Dana"]` |
| `passedNames(st, 11)` | `[]` |

---

## Exercise 6: `chunk(arr, size)`

Split the array into pieces of `size` elements each. The last piece can be shorter.

| Call | Expected |
|---|---|
| `chunk([1,2,3,4,5], 2)` | `[[1,2],[3,4],[5]]` |
| `chunk([1,2,3], 3)` | `[[1,2,3]]` |
| `chunk([1,2], 5)` | `[[1,2]]` |
| `chunk([], 2)` | `[]` |

---

## Cheat sheet

**Arrays**

| Need | Code |
|---|---|
| Loop | `for (const x of arr) { ... }` or `for (let i = 0; i < arr.length; i++)` |
| Add to the end | `arr.push(x)` |
| Contains? | `arr.includes(x)` / `arr.indexOf(x) !== -1` |
| Part of an array | `arr.slice(start, end)` (doesn't change `arr`) |
| Copy | `arr.slice()` or `[...arr]` |
| Keep some items | `arr.filter(x => x > 5)` |
| Transform each | `arr.map(x => x * 2)` |
| Sum | `arr.reduce((s, x) => s + x, 0)` |
| First match | `arr.find(x => x.id === 2)` (returns `undefined` if none) |
| Any / all | `arr.some(fn)` / `arr.every(fn)` |
| String ↔ array | `"a b".split(" ")` / `arr.join(", ")` |
| Sort numbers | `arr.sort((a, b) => a - b)` |
| Last item | `arr[arr.length - 1]` or `arr.at(-1)` |

**Objects**

| Need | Code |
|---|---|
| Read a property | `obj.name` or `obj["name"]` |
| Read with a variable key | `obj[key]` (**not** `obj.key`) |
| Loop over keys | `for (const key in obj) { ... obj[key] ... }` |
| Keys / values / pairs | `Object.keys(obj)`, `Object.values(obj)`, `Object.entries(obj)` |
| Has a key? | `key in obj` |
| Count things | `counts[w] = (counts[w] || 0) + 1;` |
| Copy | `{...obj}` or `Object.assign({}, obj)` |
| Remove a property | `delete obj.key` |

---

## Traps

- **`sort()` with no argument sorts as strings:** `[10,9,1].sort()` gives `[1,10,9]`. For numbers, use `.sort((a, b) => a - b)`.
- **`==` doesn't compare array contents:** `[1,2] == [1,2]` is `false`.
- **Arrays and objects are references:** `let b = a; b.push(9);` changes `a` too. Copy first with `arr.slice()` or `[...arr]`. Both are shallow copies: objects inside the array are still shared.
- **`obj.key` vs `obj[key]`:** with a variable key, `obj.key` looks for a property literally named `"key"`.
- **Splitting on spaces leaves empty strings:** `"  a  b".split(" ")` contains `""` items. Add `.filter(w => w !== "")`.
- **Rounding to 2 decimals:** `Math.round(x * 100) / 100` returns a number. `x.toFixed(2)` returns a **string** (`"9.00"`), which fails a test expecting `9`.
