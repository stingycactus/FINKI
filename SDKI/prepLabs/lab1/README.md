# SDKI prep: Lab 1 (color memory game, plain JS)

**The lab:** 5 boxes in different colors. You get 5 seconds to memorize the order, and the input is disabled during that time. After 5 s the boxes turn gray and the input unlocks. You type the colors (`yellow, green, blue, black, purple`), press **Submit**, and get `alert("ti si pobednik")` if the order is right, otherwise `alert("greska")`.

**Based on:** IA_AV02 (JavaScript) for everything in JS, and IA_AV1 (HTML/CSS) for the boxes. jQuery (AV03) is for later labs, so it's not used here. Each section says which aud slide it comes from. The few things the auds don't cover but the lab needs (`split`, `trim`, `toLowerCase`, `.disabled`) are marked **not in auds**.

Wherever there's a more modern way than the auds show, a **Modern:** line gives it. Both versions work in the lab.

Part 1 builds **one practice page, `practice.html`**. Each exercise adds to the previous one, and by 1.8 the page has every piece the lab needs. Part 2 is the lab itself.

Workflow: open the file in Chrome, press `F12` → **Console**. Errors show up there in red, with a line number. Refresh (`Ctrl+R`) after each change.

---

# 1. Concepts

## 1.1 Page skeleton: `<script>`, `onload`, `alert`, `console.log` (AV02 slides 4–12, 45)

The auds do it this way: functions go in a `<script>` in `<head>`, and HTML attributes call them (`onload`, `onclick`). The **Calculator** (slide 45) starts with `<body onLoad="Calculate()">`, which runs once the page has loaded. That's exactly what the lab needs to start the 5-second timer.

```html
<!DOCTYPE html>
<html>
<head>
  <title>Practice</title>
  <style>
    /* CSS goes here (AV1: embedded style) */
  </style>
  <script>
    function start() {
      console.log("page loaded");
    }
  </script>
</head>
<body onload="start()">
  <h1 id="title">Practice</h1>
</body>
</html>
```

- Why `onload` matters: code in `<head>` runs **before** the body exists. A function that runs immediately (not inside a function called by `onload`/`onclick`) and calls `getElementById` gets `null`. Inside `start()` it's fine, because `onload` waits for the page.
- Output (slides 10–12): `console.log()` is for you (Console), `alert()` is the popup the lab uses, and `innerHTML` writes into the page.
- Skip `<!-- hide -->` and `language="JavaScript"`. The auds say yourself that HTML5 doesn't need them.
- **Modern:** keep the HTML free of JS and wait for the page from inside the script:
  ```js
  document.addEventListener("DOMContentLoaded", () => {
      // runs once the HTML is parsed (a bit earlier than onload, which also waits for images)
  });
  ```
  Or put the script in its own file with `<script src="script.js" defer></script>` in `<head>`. `defer` runs the file after the HTML is parsed, so no wrapper is needed at all.
- Careful with `DOMContentLoaded`: functions declared **inside** the callback are local to it. An HTML attribute like `onclick="check()"` can't see them. If you go the modern way, attach the click with `addEventListener` too (1.7).

**Exercise:** create `practice.html` (above). Check that `page loaded` shows in the Console. Then add `console.log(document.getElementById("title"));` **outside** the function, directly in `<script>`, and see `null`. Move the line into `start()` and see the element.

## 1.2 Variables and arrays (AV02 slides 16, 27–30)

- `var colors = ["red", "yellow", "green"];` (the auds use `var`).
- **Modern:** `const` by default and `let` when you reassign, never `var`. `var` ignores `{ }` blocks and can be used before its line (as `undefined`). `let`/`const` give a clear error instead: `Cannot access 'x' before initialization`.
- **Modern strings:** template literals with backticks, `` `${i + 1}. ${colors[i]}` `` instead of `(i + 1) + ". " + colors[i]`.
- `colors[0]` is `"red"`, `colors.length` is `3`, and `colors.push("blue")` adds to the end. `toString()` gives `"red,yellow,green"`.
- Loop exactly like slide 30: `for (var i = 0; i < colors.length; i++) { ... colors[i] ... }`

**Exercise** (inside `start()`, results in the Console):
1. `var colors = ["red", "yellow", "green", "blue", "purple"];`
2. Log the length, the first and last element (`colors[colors.length - 1]`), and `colors.toString()`.
3. Loop and log `1. red`, `2. yellow`, ... (string + number, slide 14: `(i + 1) + ". " + colors[i]`).

## 1.3 Functions and strings: parsing what the user typed (AV02 slides 14, 26; split/trim **not in auds**)

- Functions (slide 26): `function name(a, b) { ... return value; }`
- The user types `"Yellow, green ,BLUE"`. You need `["yellow", "green", "blue"]`:
  - `text.split(",")` → `["Yellow", " green ", "BLUE"]` (string → array, cut at every comma)
  - `s.trim()` removes the spaces at both ends, and `s.toLowerCase()` fixes the case

```js
function parseColors(text) {
  var parts = text.split(",");
  var result = [];
  for (var i = 0; i < parts.length; i++) {
    var c = parts[i].trim().toLowerCase();
    if (c != "") {              // skip empty pieces, e.g. from "red, blue,"
      result.push(c);
    }
  }
  return result;
}
```

**Modern:** the same thing in one chain, with `map` (apply to every element), `filter` (keep the matching ones) and arrow functions (`s => ...` is short for `function (s) { return ...; }`, the callback idea from the end of AV02):
```js
const parseColors = text =>
  text.split(",").map(s => s.trim().toLowerCase()).filter(s => s !== "");
```

**Exercise:** write `parseColors` with the loop first, then the modern way. Put it outside `start()`, next to it, and test it in `start()`:
- `parseColors("Yellow, green ,BLUE")` → `["yellow", "green", "blue"]`
- `parseColors("red, green,")` → `["red", "green"]` (no empty one at the end)

## 1.4 Comparing two arrays (the trap) (AV02 slides 18, 31: arrays are objects)

- Slide 31: arrays are objects. `==` / `===` on two objects checks whether they are **the same object**, not the same contents, so `["red"] == ["red"]` is **`false`**.
- Fix: compare the lengths, then element by element with `!=`. Use `===`/`!==` (slide 18) if you want no type conversion. Here both sides are strings, so either works.

**Exercise:** write `sameSequence(a, b)`. Tests:
```js
sameSequence(["red", "blue"], ["red", "blue"])   // true
sameSequence(["red", "blue"], ["blue", "red"])   // false (order matters)
sameSequence(["red"], ["red", "blue"])           // false (length)
```
(Shortcut once you understand it: `a.toString() == b.toString()` compares two strings.)

**Modern:** `a.length === b.length && a.every((c, i) => c === b[i])`. `every` returns `true` only if the test passes for every element. Also use `===` / `!==` everywhere by default, since `==` converts types (`0 == ""` is `true`).

## 1.5 DOM: finding elements and changing their style (AV02 slides 9, 33–39)

- `document.getElementById("id")` (slide 34) returns one element.
- Change content with `el.innerHTML = "..."` (slide 34), and style with `el.style.color = "#ff0000"` (slide 38). The CSS property `background-color` becomes camelCase in JS: `el.style.backgroundColor = "red"`.
- 5 boxes → simplest aud-style: give them ids `box0` … `box4` and loop: `document.getElementById("box" + i)`.
- **Modern:**
  - `document.querySelector("#title")` takes any CSS selector (AV1) and returns the first match.
  - `document.querySelectorAll(".box")` returns all matches, so no ids are needed. Loop over the result with `.forEach((box, i) => box.style.backgroundColor = colors[i])`.
  - Use `textContent` instead of `innerHTML` when you only set text. `innerHTML` parses HTML, which is unsafe with user input.
  - For style, toggling a CSS class (`el.classList.add("gray")`) is cleaner than setting `.style` in JS. For this lab, though, `.style.backgroundColor` is simpler because every box gets a different color.

**Exercise:**
1. Add 5 boxes to `practice.html`: `<div id="box0" class="box"></div>` … `box4`. CSS in `<style>` (AV1 slides 14–21, box model slide 30): `.box { width: 80px; height: 80px; display: inline-block; margin: 5px; border: 1px solid #333; }`
2. In `start()`, loop and set `getElementById("box" + i).style.backgroundColor = colors[i]`.
3. Write `makeGray()`, which sets every box to `"gray"`. Call it from the Console by typing `makeGray()`.

## 1.6 Inputs: `.value` and `.disabled` (AV02 slide 40; disabled **not in auds**)

- Validation (slide 40) reads an input with `document.getElementById("numb").value`. That's the text the user typed, always a string.
- `el.disabled = true;` locks an input or button (grayed out, can't type or click), and `false` unlocks it. In HTML you can start locked: `<input id="answer" disabled>`.
  - It's the same idea as `src` in slide 36 (changing an attribute from JS), just a different attribute.

**Exercise:** add `<input id="answer" type="text" disabled>` and `<button type="button" id="submit" disabled>Submit</button>`. From the Console, unlock both: `document.getElementById("answer").disabled = false`.

## 1.7 Events: reacting to a click (AV02 slides 32, 34, 40)

The aud way, which is all you need: an `onclick` attribute calls your function.

```html
<button type="button" onclick="check()">Submit</button>
```

- That's exactly the validation example (slide 40): a button with `onclick="myFunction()"` reads `.value`, checks it, and shows the result. The lab is the same shape with `alert` instead of `innerHTML`.
- **Modern:** keep JS out of the HTML and attach the event in the script:
  ```js
  document.getElementById("submit").addEventListener("click", check);   // check, NOT check()
  ```
  With `check()` the function runs immediately, once, and its result gets attached. One element can have several listeners this way, and it's the only way that works if your functions live inside `DOMContentLoaded` (1.1).
  Bonus, submit on Enter: `answer.addEventListener("keydown", e => { if (e.key === "Enter") check(); });`
- `type="button"`: if the button is ever inside a `<form>`, a normal button submits the form and reloads the page, which wipes your game. `type="button"` stops that.

**Exercise:** write `check()`. It reads `answer`'s value, calls `parseColors`, compares the result with `colors` using `sameSequence`, and shows `alert("correct")` or `alert("wrong")`. Unlock the input from the Console and test the right and the wrong order.
(`colors` has to be **global** for `check()` to see it, so declare it outside `start()`, at the top of the script. Slide 26: variables declared in a function are local.)

## 1.8 Timer: `setTimeout` (AV02 slide 48, "Simple animation")

- `setTimeout(fn, 5000)` runs `fn` **once**, after 5000 ms.
- The aud writes `setTimeout("nextFrame()", 50)` (code as a string). It works, but the better form is to pass the function itself: `setTimeout(nextFrame, 50)`.
- Trap: `setTimeout(makeGray(), 5000)` runs `makeGray` **right now** (the `()` calls it) and turns gray immediately.
- Code after `setTimeout` does not wait: the timer starts and the next line runs at once.
- The animation also shows the **countdown pattern**: a function that does one step and then calls `setTimeout` on itself again until a counter runs out.

```js
var seconds = 5;
function tick() {
  document.getElementById("timer").innerHTML = seconds;
  if (seconds > 0) {
    seconds--;
    setTimeout(tick, 1000);   // call myself again in 1 s (same as nextFrame)
  }
}
```

**Modern countdown:** `setInterval(fn, 1000)` runs `fn` **every** second until you stop it:
```js
let seconds = 5;
timer.textContent = seconds;            // show 5 right away: setInterval waits 1 s before its first run
const id = setInterval(() => {
  seconds--;
  timer.textContent = seconds;
  if (seconds === 0) clearInterval(id); // stop at 0
}, 1000);
```
The self-calling `setTimeout` from the aud is also still fine.

Why a countdown needs a timer **every second** when the lab only needs one `setTimeout(..., 5000)`: the 5000 ms timer fires once, at the end. The countdown number has to change every second, so something must run every second. The countdown is only an optional display on top. You can also call `endMemorize()` from the countdown when it hits 0 and drop the 5000 ms timer, so one timer drives both.

**Exercise:**
1. In `start()`, after painting the boxes: `setTimeout(endMemorize, 5000);`. `endMemorize()` calls `makeGray()` and unlocks the input and the button. **This is now the whole lab** with fixed colors. Play it once.
2. Add `<p id="timer"></p>` and the countdown above, started from `start()` with `tick();`. It should show 5, 4, ... 0 and stop.

---

# 2. The lab

New file `lab1/index.html`, everything in one file like the aud examples (`<style>` + `<script>` in `<head>`).

The steps below follow the aud way. The modern way swaps in, step by step:
- `DOMContentLoaded` or `defer` instead of `onload`
- `addEventListener("click", check)` instead of `onclick="check()"`
- `querySelectorAll(".box")` instead of ids `box0`…`box4`
- `const`/`let`, `map`/`filter` and `every` instead of `var` and loops

Pick one style and stay consistent.

Build in this order, and test after each step:

1. **HTML**: title, 5 boxes `box0`…`box4`, `<input id="answer" disabled>`, `<button type="button" id="submit" disabled onclick="check()">Submit</button>`, `<body onload="start()">`.
2. **CSS**: box size, `inline-block`, border (1.5).
3. **Colors**: a global array of 5 **different** colors with names the user can type: `red`, `yellow`, `green`, `blue`, `black`, `purple`, `orange`, `pink` (not hex codes).
4. **`start()`**: paint the boxes (1.5), then `setTimeout(endMemorize, 5000)` (1.8).
5. **`endMemorize()`**: boxes gray, input and button `disabled = false`, plus `focus()` on the input (a nice extra, so you can type right away).
6. **`check()`**: parse (1.3) → compare (1.4) → `alert("ti si pobednik")` / `alert("greska")`.
7. Extra (only if there's time): a countdown (1.8), or random colors each refresh (pick from a list of 8 with `Math.floor(Math.random() * list.length)`, skipping ones already taken with `indexOf(c) == -1`).

**Test checklist**
- During the first 5 s you can't type in the input or click the button.
- After 5 s the boxes are all gray and you can type.
- Correct order → `ti si pobednik`, also with different case and spacing: `Yellow,green , BLUE ,...`.
- Correct colors in the wrong order → `greska`. 4 colors only → `greska`. Empty input → `greska`.

**Common mistakes**
- `getElementById` running directly in `<head>` (not inside a function) → `null` / `Cannot read properties of null`. Put it in `start()`, called by `onload`.
- `colors` declared inside `start()` → `check()` says `colors is not defined`. Make it global.
- `getElementById(title)` without quotes → it looks up a variable, not the id. Ids are strings: `getElementById("title")`.
- Functions inside `DOMContentLoaded` + `onclick="check()"` in HTML → `check is not defined`. Use `addEventListener` instead.
- Comparing arrays with `==` → always `greska`.
- `setTimeout(makeGray(), 5000)` → turns gray immediately.
- Forgetting `trim()` / `toLowerCase()` → `" green"` doesn't match `"green"`.
- `grey` vs `gray`: CSS accepts both, but your comparison doesn't. Another reason to use simple names.

Sources: SDKI auditory exercises IA_AV1 (HTML/CSS) and IA_AV02 (JavaScript).
