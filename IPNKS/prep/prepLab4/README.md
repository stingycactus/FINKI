# IPNKS prep: Lab 4 (DOM + events)

**The lab (last year's version):** three small pages. (1) A number input that shows `Even` / `Odd` live on every key press. (2) A password input that live-highlights a `Weak` / `Medium` / `Strong` indicator and shows an `alert` with the strength when you finish typing. (3) A lightblue ball inside a frame: it grows 20% and turns pink on hover, goes back on mouse leave, and a `Bounce` button moves it to a random spot inside the frame with a random color. Full texts and test cases are in Part 2.

**Based on:** the DOM lecture (`IP-2025.2026-DOM.pdf`, slide numbers below), AV3 (strings) and the style of the posted kolokvium solutions (`onclick="..."` attributes, `getElementById`, `innerHTML`). **Events** (`onkeyup`, `onmouseover`, ...) and CSS positioning are **not in auds**: they're marked that way.

Wherever there's a more modern way, a **Modern:** line gives it. Both versions work in the lab.

Part 1 builds one practice page, `practice.html`, in this folder. Each exercise adds to it. By 1.10 it contains every mechanic of the three lab tasks. Part 2 is the lab itself.

**Workflow:** open the file in the browser (WebStorm: right-click → Open in → Browser, or Live Server), keep **F12 → Console** open, save + refresh after every change. Red text in the Console = your bug.

---

# 1. Concepts

## 1.1 Page skeleton and `getElementById` (DOM slides 12, 19)

- `document.getElementById("x")` returns the element with `id="x"`, or **`null`** if it doesn't exist (yet).
- A script runs the moment the browser reads it. A script in `<head>` that grabs elements at the top level gets `null`, because `<body>` isn't parsed yet (slide 12).
- Safe options: put the `<script>` at the **end of `<body>`**, or only touch elements **inside functions** that run later (on a click/key). The kolokvium solutions put functions in `<head>`: that's fine because the functions only run after a click.
- **Modern:** `document.querySelector("#x")` (any CSS selector, slide 22). `<script defer>` in `<head>` also waits for the page.

```html
<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>Practice</title></head>
<body>
  <p id="msg">Hello</p>
  <script>
    const msg = document.getElementById("msg");
    console.log(msg);
  </script>
</body>
</html>
```

**Exercise:**
1. Create `practice.html` with the code above. The Console shows `<p id="msg">Hello</p>`.
2. Break it on purpose: move the `<script>` into `<head>`. The Console shows `null`. Then add `msg.textContent = "x";` and read the error: `Cannot read properties of null (reading 'textContent')`. Move it back.

## 1.2 Reading an input: `.value` (DOM slide 42)

- `input.value` is what's typed right now. It is **always a string**, even for `type="number"`: `"234"`, not `234`.
- Convert: `Number(v)` or `parseInt(v)` / `parseFloat(v)`. `Number("")` is `0` (trap), so check for empty first.
- `type="number"` quirk: while the text is not a valid number yet (`-`, `1e`), `.value` is `""`.
- Check if it's a whole number: `Number.isInteger(n)`; not a number at all: `isNaN(n)`.

```js
const v = document.getElementById("num").value;   // "234"
if (v === "") { /* nothing typed / not valid yet */ }
const n = Number(v);                               // 234
```

**Exercise:**
1. Add `<input type="number" id="num">` and `<button onclick="readIt()">Read</button>`. Write `readIt()` that logs `typeof v`, `v` and `Number(v)`. Type `42`, click: `string 42 42`.
2. Type only `-` and click: `v` is `""`. Note this, it matters in the lab.

## 1.3 Writing output: `textContent` vs `innerHTML` (DOM slides 31, 36-37)

- `el.textContent = "Even"` puts plain text in. `el.innerHTML = "<b>Even</b>"` parses HTML.
- The kolokvium solutions use `innerHTML` for everything. For plain text, `textContent` is safer (user input like `<b>` stays literal, slide 37).
- To clear: `el.textContent = ""`.
- Show/hide: `el.hidden = true / false` (slide 38).

**Exercise:**
1. Add `<span id="out"></span>` next to the input. In `readIt()`, write `"You typed " + v` into it.
2. Type into a text input `<b>hi</b>` once with `innerHTML` and once with `textContent` (change `type="number"` to `text` temporarily) and see the difference.

## 1.4 Events: running code on key press, click, change (not in auds)

- An **event handler** is a function the browser calls when something happens. Course style: an attribute with the call inside: `onclick="readIt()"`.
- Key events on an input, **in this order**: `keydown` → `keypress` → (the character is added to `.value`) → `keyup`.
- So `onkeydown` / `onkeypress` see the **old** value (one character behind). Use **`onkeyup`** to read the updated value.
- `onchange` fires when you **finish** editing: on **Enter** or when the input **loses focus** (click elsewhere/Tab), and only if the value changed. `onblur` fires on every focus loss.
- **Modern:** `el.addEventListener("input", check)` fires on every value change, including paste and the number spinner arrows (`keyup` misses mouse clicks on the spinner). Pass the function, no `()`.
- Trap: `addEventListener("keyup", check())` calls `check` right now, once. Write `check` without `()`.

| Course way | Modern |
|---|---|
| `<input onkeyup="check()">` | `num.addEventListener("input", check);` |
| `<button onclick="go()">` | `btn.addEventListener("click", go);` |
| `<input onchange="done()">` | `pass.addEventListener("change", done);` |

**Exercise:**
1. Add `onkeyup="readIt()"` to the input. Now `out` updates while typing, no button needed.
2. Break it on purpose: change it to `onkeypress`. Type `123`: the span shows `You typed 12` (one behind). Change back to `onkeyup`.
3. Add `onchange="console.log('changed')"`. It logs when you press Enter or click outside, not while typing.

## 1.5 Numbers: `%` and the negative trap (AV2 operators)

- `n % 2` is the remainder: `0` for even. Test with `n % 2 === 0`.
- Trap: `-3 % 2` is **`-1`**, not `1`. So `n % 2 === 1 ? "Odd" : "Even"` says `-3` is Even. Always test `=== 0`.
- Ternary for short choices: `const s = n % 2 === 0 ? "Even" : "Odd";`

**Exercise:** make the practice input live-show divisibility by **3** instead:
1. `readIt()`: if `v === ""` clear `out` and `return`. If the number isn't an integer show `Not an integer`. Else show `Divisible by 3` or `Not divisible by 3`.
2. Expected:

```
9    -> Divisible by 3
10   -> Not divisible by 3
-9   -> Divisible by 3
-10  -> Not divisible by 3   (check: -10 % 3 is -1)
2.5  -> Not an integer
-    -> (empty)
```

## 1.6 Checking characters in a string (AV3 strings)

- `s.length`, `s.charAt(i)` (or `s[i]`), loop `for (let i = 0; i < s.length; i++)`.
- Characters compare by code: `c >= "A" && c <= "Z"` is an uppercase letter, `c >= "0" && c <= "9"` a digit, `c >= "a" && c <= "z"` lowercase. Anything else = a symbol (for this lab).
- Use boolean flags: set `hasUpper = true` when you see one.
- **Modern (not in auds):** regular expressions: `/[A-Z]/.test(s)`, `/[0-9]/.test(s)`, `/[^A-Za-z0-9]/.test(s)` (`^` inside `[]` means "not").

```js
let hasUpper = false, hasDigit = false, hasSymbol = false;
for (let i = 0; i < s.length; i++) {
  const c = s.charAt(i);
  if (c >= "A" && c <= "Z") hasUpper = true;
  else if (c >= "0" && c <= "9") hasDigit = true;
  else if (!(c >= "a" && c <= "z")) hasSymbol = true;
}
```

**Exercise:** add a username field to the practice page.
1. `<input type="text" id="user" onkeyup="checkUser()">` and `<span id="info"></span>`. Show `length: L, upper: U, digits: D, symbols: S` (counts, not flags).
2. Expected: `Ana_99` → `length: 6, upper: 1, digits: 2, symbols: 1`. `ana` → `length: 3, upper: 0, digits: 0, symbols: 0`.
3. Write a function `userLevel(s)` that **returns** `"Short"` (length ≤ 3), `"OK"` (4 to 8) or `"Long"` (more than 8). Test it in the Console first: `userLevel("ana")` → `"Short"`. Keep the logic in a returning function: you'll reuse it for the alert in 1.8.

## 1.7 Styling from JS: `style` and classes (DOM slides 4, 19, 43)

- `el.style.background = "red"` sets an inline style. CSS names with `-` become camelCase: `font-weight` → `style.fontWeight`.
- Reading `el.style.width` only returns inline styles (`""` if the width came from a `<style>` sheet). Read real sizes with `el.offsetWidth` (number, pixels).
- Classes: `el.className = "box active"` (replaces all classes). **Modern:** `el.classList.add("active")`, `.remove("active")`, `.toggle(...)`, `.contains(...)`.
- "Highlight one of three" pattern: remove `active` from all three, then add it to the right one.

```css
.ind { padding: 4px 10px; border: 1px solid #999; color: #999; }
.ind.active { background: green; color: white; }
```

**Exercise:**
1. Add three spans: `<span id="short" class="ind">Short</span>`, `ok`, `long`. In `checkUser()`, highlight the one matching `userLevel(...)`. Typing `an` → only Short is highlighted; `anabanana1` → only Long.
2. Do it once with `style.background` and once with `classList`. Note how much simpler resetting is with classes.

## 1.8 "When input is finished": `onchange` + `alert` (not in auds)

- Add `onchange="userDone()"` to the username input. `userDone()` does `alert("Username level: " + userLevel(value))`.
- `alert` blocks the page until OK is clicked. Don't call it from `onkeyup` (it would pop on every key).
- `onkeyup` and `onchange` can sit on the same input: `<input onkeyup="a()" onchange="b()">`.

**Exercise:**
1. Type `Ana_99`, press **Enter** → alert `Username level: OK`. Type more, click outside → alert again.
2. Click in and out without changing anything → no alert (`change` needs a new value). Switch to `onblur` and see it fire every time.

## 1.9 Positioning inside a frame (CSS, not in auds)

- Parent: `position: relative` (the frame becomes the reference). Child: `position: absolute; left: ...; top: ...;` is measured from the frame's top-left corner.
- A circle: equal `width` and `height` + `border-radius: 50%`.
- Setting position from JS **needs the unit**: `ball.style.left = x + "px";`. `ball.style.left = x` silently does nothing.
- Inner frame size: `frame.clientWidth` / `clientHeight` (without the border). Element size: `el.offsetWidth` / `offsetHeight`.
- Max position so the child stays fully inside: `frame.clientWidth - el.offsetWidth`.

```css
#frame { position: relative; width: 350px; height: 180px; border: 1px solid #aaa; }
#box   { position: absolute; left: 20px; top: 20px; width: 40px; height: 40px; background: green; }
```

**Exercise:**
1. Add the frame with a green square `#box` and `<button onclick="moveBox()">Move</button>`. First, `moveBox()` moves the box to the bottom-right corner exactly (`left = clientWidth - offsetWidth`). Check that it touches the corner without poking out.
2. Break it on purpose: drop `+ "px"`. The box doesn't move, and there's no error.

## 1.10 Random numbers and colors (AV4b uses `Math.random`)

- `Math.random()` → a decimal in `[0, 1)`. Random integer from `0` to `max` inclusive: `Math.floor(Math.random() * (max + 1))`.
- Random color, simple: `"rgb(" + r + "," + g + "," + b + ")"` with each from 0 to 255. **Modern:** template literal `` `rgb(${r}, ${g}, ${b})` ``.
- Random hex alternative: `"#" + Math.floor(Math.random() * 16777216).toString(16).padStart(6, "0")`.

**Exercise:**
1. Write `randInt(max)` returning `0..max`. In the Console, run `randInt(2)` many times: you see 0, 1 and 2, never 3.
2. Make `moveBox()` move the box to a random spot inside the frame (use the max from 1.9) and give it a random color. Click 20 times: it never pokes out of the frame.

## 1.11 Hover: `onmouseover` / `onmouseout` (not in auds)

- `onmouseover` fires when the pointer enters the element, `onmouseout` when it leaves. (`onmouseenter`/`onmouseleave` are similar and don't bubble from children; for a single div either pair works.)
- Grow by 20%: `el.style.transform = "scale(1.2)"`; reset with `el.style.transform = ""`. It grows around the center and doesn't move other elements. Alternative: set `width`/`height` to `offsetWidth * 1.2` + `"px"` and back (it grows from the top-left corner).
- "Return to original color": if a click already changed the color, store the current color in a variable before overwriting it on hover, otherwise mouseout resets it to the starting color. Decide which one the task means and be consistent.
- **CSS-only way:** `#box:hover { transform: scale(1.2); background: pink; }`. Short, but inline `style.background` set by JS beats the `:hover` rule, so after a JS color change the hover color stops working. Use JS events for the lab.

**Exercise:**
1. On `#box`: `onmouseover="boxIn()" onmouseout="boxOut()"`. `boxIn()` scales it to 1.2 and makes it orange. `boxOut()` resets the scale and color.
2. Click Move (random color), hover → orange, leave → back to the random color, not green. You now have every mechanic of the lab.

---

# 2. The lab

Pick one style per page (course `on...=""` attributes or `addEventListener`) and stay consistent. Same tasks as last year are likely, maybe with changed details: read the spec slowly.

## Task 1: Even / Odd

> Да се креира веб страница која содржи едно поле за внесување број. При секое притискање на копче од тастатура во полето, програмата треба да провери дали внесениот број е парен или непарен и да го прикаже резултатот.
>
> Create a website that contains a single number input field. With every key press inside the field, the program should check whether the entered number is even or odd and display the result on the page.

Screenshot: label `Enter a number:`, under it the input, and the result (`Even`) right next to the input.

**Build order:** skeleton + input + result span (1.1, 1.3) → `onkeyup` handler (1.4) → read + empty check (1.2) → `% 2 === 0` (1.5).

| Type | Expected |
|---|---|
| `234` | `Even` (shown after each key: `2` Even, `23` Odd, `234` Even) |
| `7` | `Odd` |
| `0` | `Even` |
| `-3` | `Odd` (not `Even`!) |
| `-` only | nothing (value is `""`) |
| delete everything | result clears (not `Even` from `Number("") = 0`) |
| `2.5` | your choice, e.g. `Not an integer` (`2.5 % 2` is `0.5`: neither) |
| `12`, then press ↑ arrow | `13` → `Odd` (keyup fires for arrow keys too) |

## Task 2: Password strength

> Да се креира веб страница со поле за внесување лозинка. При секое притискање на копче во полето, програмата проверува јакоста на лозинката и го осветлува соодветниот индикатор: „Weak" (до 4 карактери), „Medium" (до 7 карактери, вклучувајќи голема буква или бројка) или „Strong" (повеќе од 7 карактери, голема буква или бројка и знак). По завршување на внесувањето, се прикажува alert со јачината на лозинката.
>
> Create a website with a password input field. With every key press in the field, the program checks the password strength and highlights the matching indicator: "Weak" (up to 4 characters), "Medium" (up to 7 characters, including an uppercase letter or a digit) or "Strong" (more than 7 characters, an uppercase letter or a digit, and a symbol). When input is finished, an alert shows the password strength.

The spec has gaps (a 6-letter lowercase password, an 8-char one without a symbol). A sensible reading, checked from strongest down:

- **Strong:** length > 7 **and** (uppercase or digit) **and** a symbol.
- **Medium:** length > 4 **and** (uppercase or digit).
- **Weak:** everything else.

If the assistant reads it differently, follow them. Whatever rule you pick, write it in a comment at the top.

**Build order:** `<input type="password">` + three indicator spans (1.7) → `strength(p)` returning `"Weak"/"Medium"/"Strong"` (1.6), tested in the Console → `onkeyup` highlights (1.4, 1.7) → `onchange` alert (1.8).

| Type | Length | Expected highlight |
|---|---|---|
| `abc` | 3 | Weak |
| `abcd` | 4 | Weak |
| `abcde` | 5 | Weak (no uppercase/digit) |
| `Abcde` | 5 | Medium |
| `abc12` | 5 | Medium |
| `Abcdefg` | 7 | Medium |
| `abcdefgh` | 8 | Weak |
| `Abcdefgh` | 8 | Medium (no symbol) |
| `abcdefg!` | 8 | Weak (symbol but no uppercase/digit) |
| `Abcdefg!` | 8 | Strong |
| `12345678#` | 9 | Strong |
| type `Abcdefg!`, press Enter | | alert `Password strength: Strong` (wording is yours) |
| delete back to `Ab` | | highlight goes back to Weak (only one indicator lit at a time) |

## Task 3: Bounce ball

> Да се креира веб страница која содржи плава топка внатре во рамка и копче „Bounce". При hover на топката, таа се зголемува за 20% и ја менува бојата во розева. При тргање на маусот од топката, таа се враќа на оригиналната големина и боја. При клик на копчето „Bounce", топката се преместува во случајна позиција внатре во рамката и ја менува бојата на случајна боја.
>
> Create a website that contains a lightblue ball inside a frame and a button „Bounce". When hovering over the ball, it increases in size by 20% and changes its color to pink. When the mouse leaves the ball, it returns to its original size and color. On click of the „Bounce" button, the ball moves to a random position inside the frame and changes to a random color.

Screenshot: a gray-bordered frame (about 350×180), a lightblue circle near the top-left, the `Bounce` button under the frame.

**Build order:** frame + ball CSS (1.9) → hover in/out (1.11) → random position (1.9, 1.10) → random color (1.10) → decide what "original color" means after a bounce (1.11).

| Do | Expected |
|---|---|
| Load | lightblue (`rgb(173, 216, 230)`) circle inside the frame |
| Hover the ball | 20% bigger (40px → 48px), pink |
| Move the mouse away | back to 40px, lightblue |
| Click Bounce 20 times | every time a new spot, always fully inside the frame, new color |
| Bounce, then hover, then leave | pink on hover; on leave back to the bounced color (or lightblue, if you read "original" literally: say which in a comment) |
| Check in F12 → Elements | `left`/`top` change as `...px` on the ball's `style` |

## Common mistakes

| Symptom | Cause | Fix |
|---|---|---|
| `Cannot read properties of null (reading 'value')` | script runs before the element exists, or the id is misspelled | script at the end of `<body>` / code inside functions; check the id |
| Result is one key behind | `onkeypress` / `onkeydown` | `onkeyup` (or modern `input` event) |
| Empty field shows `Even` | `Number("")` is `0` | `if (v === "")` first |
| `-3` shows `Even` | `-3 % 2` is `-1` | test `% 2 === 0` |
| `f is not defined` when the event fires | function declared inside `DOMContentLoaded`/another function, but called from an `on...=""` attribute | keep handler functions at the top level of the script |
| Handler runs once at load, then never | `addEventListener("click", f())` | pass `f`, no `()` |
| Several indicators lit at once | added `active` without removing it from the others | remove from all three, then add one |
| Alert pops on every key | `alert` inside the keyup handler | alert only in `onchange` |
| Ball doesn't move, no error | `style.left = x` without `"px"` | `x + "px"` |
| Ball pokes out of the frame | random range uses the full frame width | `frame.clientWidth - ball.offsetWidth` |
| Ball moves relative to the page | frame missing `position: relative` | add it |
| Hover pink stops working after Bounce | CSS `:hover` vs inline `style.background` | do hover with JS events |

Sources: `IP-2025.2026-DOM.pdf`, `IP_AV3_en.pdf`, `IP_AV4b_en.pdf`, posted kolokvium solutions in the IPNKS project.
