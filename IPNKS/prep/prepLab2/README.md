# IPNKS prep: Lab 2 (string functions)

**The lab:** write three JavaScript functions that take a string and `return` a result. Each function is checked with 5 tests worth 0.2 points each. No `prompt` and no `alert`, only `return`. You can add helper functions.

1. `isStrongPassword(password)` returns `true` only if the password has **at least 8 characters**, **at least one uppercase letter (A–Z)**, **at least one lowercase letter (a–z)** and **at least one digit (0–9)**. Spaces and punctuation are allowed and count toward the length.
2. `toSlug(title)` lowercases the title, keeps `a–z` and `0–9`, replaces **each group** of other characters with **one** `-`, and never starts or ends with `-`. A title with no letters or digits gives `""`. Example: `"Internet Programming: Lab 2!"` → `"internet-programming-lab-2"`.
3. `getDomain(url)`, steps in this order: lowercase it; remove `http://` or `https://`; remove `www.`; then keep the text up to the first `/`, `?`, `#` or `:`. If none of those appear, keep the whole remaining text.

**Based on:** AV1 (variables, operators, `+` on strings), AV2 (`if`, loops), the *JavaScript Fundamentals* lecture (strings, loops) and the *Functions* lecture (functions, `return`, string methods on slides 46–52). The auds themselves use `prompt`/`document.write`. This lab drops both, so you practice plain functions that return values. Anything the lab needs that the auds and lectures don't cover is marked **not in auds**.

Wherever there's a more modern way than the auds show, a **Modern:** line gives it. Both versions work in the lab.

**Time: ~45 min total.** Part 1 has 5 blocks (~30 min) that all extend one `practice.html`. Part 2 is the lab: 3 functions at ~5 min each. By the end of Part 1 you will have used every technique the lab needs.

**Workflow:** open `practice.html` in Chrome, press F12, open the **Console** tab, and refresh after every change. You can also call any function directly in the Console, e.g. `isValidUsername("ok")`.

---

# 1. Concepts

## 1.1 Functions that `return` + a test helper (Functions lecture slides 3, 9–12) · 3 min

- `function name(param) { ... return value; }`. Without `return`, the result is `undefined`.
- The checker calls your function and compares what it **returns**. Whatever you `console.log` is ignored.
- A function stops at its first `return`, which makes early exits like `if (bad) return false;` possible (slide 10).
- Test with `===`, not `==` (AV1 slide 18): `"5" == 5` is `true`, `"5" === 5` is `false`.

```html
<!DOCTYPE html>
<html lang="en">
<head><meta charset="UTF-8"><title>Lab 2 practice</title></head>
<body>
<script>
    function check(label, actual, expected) {
        if (actual === expected) {
            console.log("OK   " + label);
        } else {
            console.log("FAIL " + label + ": got " + JSON.stringify(actual) + ", expected " + JSON.stringify(expected));
        }
    }

    function square(x) {
        return x * x;
    }

    check("square(3)", square(3), 9);
</script>
</body>
</html>
```

**Exercise:**
1. Save this as `practice.html` in this folder and open it. Console: `OK   square(3)`.
2. Break it on purpose: delete `return` (leave `x * x;`). Console: `FAIL square(3): got undefined, expected 9`. Put `return` back.

Leave the `check` helper at the top and add each new function and its checks below it.

## 1.2 Walking a string character by character (Fundamentals slides 36, 55–56; Functions slide 46) · 5 min

- `s.length` is the number of characters. `s[i]` is the character at index `i`, from `0` to `s.length - 1`.
- The loop is `for (let i = 0; i < s.length; i++)`. Use `<`, not `<=`.
- `s.toLowerCase()` **returns a new string** and does not change `s`. Write `s = s.toLowerCase();`.
- **Modern:** `for (const ch of s) { ... }` gives you each character directly, with no index.

```js
function countVowels(s) {
    s = s.toLowerCase();
    let count = 0;
    for (let i = 0; i < s.length; i++) {
        const ch = s[i];
        if (ch === "a" || ch === "e" || ch === "i" || ch === "o" || ch === "u") {
            count++;
        }
    }
    return count;
}
```

**Exercise:**
1. Add `countVowels` and these checks. All three should print `OK`:
   ```js
   check('countVowels("Internet Programming")', countVowels("Internet Programming"), 6);
   check('countVowels("")', countVowels(""), 0);
   check('countVowels("JS")', countVowels("JS"), 0);
   ```
2. Break it: remove the line `s = s.toLowerCase();`. The first check fails with `got 5` because the capital `I` is no longer counted. Put the line back.
3. Change `<` to `<=` and add `console.log(ch)` inside the loop. The last line printed is `undefined`, because `s[s.length]` doesn't exist. Change it back to `<`.

## 1.3 Character classes and "every" vs "at least one" (lab hint; Functions slides 9–10) · 8 min

- Characters compare alphabetically by code: `ch >= "A" && ch <= "Z"` means "ch is an uppercase Latin letter". Put this in helpers:
  ```js
  function isUpper(ch) { return ch >= "A" && ch <= "Z"; }
  function isLower(ch) { return ch >= "a" && ch <= "z"; }
  function isDigit(ch) { return ch >= "0" && ch <= "9"; }
  ```
- Trap: compare digits as **strings**, `"0"` and `"9"`. With numbers, `" " >= 0 && " " <= 9` is `true`, because a space converts to the number 0, so a space would count as a digit.
- Trap: `"Ш"`, `"Š"`, `"ć"` are **not** in `A–Z`/`a–z`. Here they count as "other" characters, and that's what the lab wants.
- **"Every character must be OK"**: inside the loop, `return false` at the first bad character, and `return true` **after** the loop.
- **"At least one X"**: set a flag `let hasX = false;` before the loop, set it to `true` inside the loop when you see an X, and check it **after** the loop.
- **Modern (not in auds):** regex tests: `/[A-Z]/.test(s)` means "s contains an uppercase letter". It's one line, but learn the loop version first.

```js
function isValidUsername(name) {
    if (name.length < 3 || name.length > 12) return false;
    if (!isLower(name[0])) return false;
    for (let i = 0; i < name.length; i++) {
        const ch = name[i];
        if (!(isLower(ch) || isDigit(ch) || ch === "_")) return false;
    }
    return true;
}
```

**Exercise:**
1. Add the three helpers and `isValidUsername` (3–12 chars, only `a–z`, `0–9`, `_`, must start with a letter). Check: `"cactus"` → `true`, `"ca"` → `false`, `"cactus_99"` → `true`, `"Cactus"` → `false`, `"9lives"` → `false`, `"a b c"` → `false`, `"abcdefghijklm"` (13 chars) → `false`.
2. Write `isNiceUsername(name)`: the name is valid **and** contains at least one digit. Use a `hasDigit` flag, not an early `return`. Check: `"cactus"` → `false`, `"cactus_99"` → `true`, `"Cactus99"` → `false`.
3. Break it: in `isDigit` replace `"0"`/`"9"` with `0`/`9`, then run `isDigit(" ")` in the Console. You get `true`. Change it back.

## 1.4 Building a new string + "one separator per group" (AV1 slides 22–24) · 8 min

- Start with `let result = "";` and add to it with `result += ch;`. Return `result` at the end.
- To replace a **group** of characters with **one** symbol, keep a flag that says whether you are currently inside a group.
- To also avoid a separator at the **start or end**, don't write the separator when the group starts. Remember that one is pending, and write it only right before the next kept character, and only if `result` isn't empty:
  ```js
  if (keep) {
      if (pending && result !== "") result += "_";
      result += ch;
      pending = false;
  } else {
      pending = true;
  }
  ```
  A group at the end never gets written, because no kept character follows it.
- **Modern (not in auds):** `s.replace(/[^a-z]+/g, "_")` replaces every group in one call. `.replace(/^_+|_+$/g, "")` then strips the separators at the ends.

```js
function maskDigits(s) {
    let result = "";
    let inRun = false;
    for (let i = 0; i < s.length; i++) {
        const ch = s[i];
        if (isDigit(ch)) {
            if (!inRun) {
                result += "#";
                inRun = true;
            }
        } else {
            result += ch;
            inRun = false;
        }
    }
    return result;
}
```

**Exercise:**
1. Add `maskDigits` (each group of digits becomes one `#`). Check: `"call 071 234 567"` → `"call # # #"`, `"a1b22c333"` → `"a#b#c#"`, `"no digits"` → `"no digits"`, `""` → `""`.
2. Write `toTag(text)`: lowercase; keep `a–z` only; each group of anything else becomes one `_`; no `_` at the start or end. Use the `pending` pattern. Check: `"Hello, World 2026!"` → `"hello_world"`, `"  --JS--  rocks "` → `"js_rocks"`, `"123"` → `""`, `"a"` → `"a"`, `"Ćao Svete"` → `"ao_svete"`.
3. Break it: write `toTag` the `maskDigits` way (add `_` as soon as a group starts). `"  --JS--  rocks "` now gives `"_js_rocks_"`. This is the exact mistake the slug rule is testing.

## 1.5 `startsWith`, `slice`, `indexOf` (Functions slides 47–51) · 8 min

- `s.startsWith("abc")` returns `true` or `false`.
- `s.slice(start, end)` returns the part from `start` up to but **not including** `end`. Leave out `end` to go to the end of the string. Remove a prefix with `s = s.slice(prefix.length)` (`"mailto:"` → `slice(7)`).
- `s.indexOf("@")` returns the position of the first `@`, or **`-1`** if there isn't one.
- Trap: `s.slice(0, -1)` cuts off the **last character**. So `"nobody".slice(0, "nobody".indexOf("@"))` returns `"nobod"`. Always handle `-1` first.
- Trap: order matters. Lowercase **before** `startsWith`, or `"MAILTO:..."` won't match `"mailto:"`.
- Stopping at the first of **several** characters: either loop over the string and `return s.slice(0, i)` at the first stop character (simplest), or take `indexOf` of each stop character and keep the smallest one that isn't `-1`.

```js
function getEmailUser(email) {
    email = email.toLowerCase();
    if (email.startsWith("mailto:")) {
        email = email.slice(7);
    }
    for (let i = 0; i < email.length; i++) {
        if (email[i] === "@" || email[i] === "+") {
            return email.slice(0, i);
        }
    }
    return email;
}
```

**Exercise:**
1. Add `getEmailUser` (lowercase; drop `mailto:`; keep text up to the first `@` or `+`). Check: `"mailto:Cactus+lab@finki.mk"` → `"cactus"`, `"Filip@Gmail.com"` → `"filip"`, `"MAILTO:ana@x.mk"` → `"ana"`, `"nobody"` → `"nobody"`, `"mailto:"` → `""`.
2. Rewrite the stop part with `indexOf`: `let end = email.length;` then for each of `"@"` and `"+"`: `const pos = email.indexOf(c); if (pos !== -1 && pos < end) end = pos;` then `return email.slice(0, end);`. All 5 checks should still print `OK`.
3. Break it: move `toLowerCase()` below the `startsWith` line. `"MAILTO:ana@x.mk"` now returns `"mailto:ana"`.

---

# 2. The lab (~15 min)

Use the same `practice.html` or a new `lab2.html` with `check` and the three character helpers at the top. The answer field already contains an HTML page with each function. Keep the function names and parameters **exactly** as given, and paste helpers (`isUpper`, ...) into the same `<script>`.

## Build order (test after each step)

1. **`isStrongPassword`** (1.3): length check with an early `return false`, then three flags (`hasUpper`, `hasLower`, `hasDigit`) in one loop, then `return hasUpper && hasLower && hasDigit;`.
2. **`toSlug`** (1.4): it's `toTag` with `-` instead of `_` and with digits kept: `isLower(ch) || isDigit(ch)`.
3. **`getDomain`** (1.5): lowercase → `startsWith("http://")` → `slice(7)`, **else** `startsWith("https://")` → `slice(8)` → `startsWith("www.")` → `slice(4)` → loop to the first `/ ? # :` → otherwise return the whole string.

## Test checklist

| Call | Expected |
|---|---|
| `isStrongPassword("Passw0rd")` | `true` |
| `isStrongPassword("Abcdefg1")` | `true` (exactly 8) |
| `isStrongPassword("Pa ss 1 x")` | `true` (spaces count toward 9) |
| `isStrongPassword("Ab1!!!!!")` | `true` |
| `isStrongPassword("password1")` | `false` (no uppercase) |
| `isStrongPassword("PASSWORD1")` | `false` (no lowercase) |
| `isStrongPassword("Password")` | `false` (no digit) |
| `isStrongPassword("Pass 1w")` | `false` (7 chars) |
| `isStrongPassword("Šifra123")` | `false` (`Š` is not A–Z) |
| `isStrongPassword("")` | `false` |
| `toSlug("Internet Programming: Lab 2!")` | `"internet-programming-lab-2"` |
| `toSlug("  Hello   World  ")` | `"hello-world"` |
| `toSlug("C++ & Java")` | `"c-java"` |
| `toSlug("-Top 10-")` | `"top-10"` |
| `toSlug("a--b")` | `"a-b"` |
| `toSlug("already-a-slug")` | `"already-a-slug"` |
| `toSlug("ABC123")` | `"abc123"` |
| `toSlug("Лаб 2 – JS")` | `"2-js"` (Cyrillic is "other") |
| `toSlug("!!!")` / `toSlug("")` | `""` |
| `getDomain("https://www.finki.ukim.mk/path?x=1#top")` | `"finki.ukim.mk"` |
| `getDomain("HTTPS://WWW.FINKI.UKIM.MK")` | `"finki.ukim.mk"` |
| `getDomain("HTTP://Example.COM")` | `"example.com"` |
| `getDomain("www.google.com/search?q=js")` | `"google.com"` |
| `getDomain("courses.finki.ukim.mk")` | `"courses.finki.ukim.mk"` |
| `getDomain("http://localhost:8080/app")` | `"localhost"` |
| `getDomain("https://site.mk?ref=1")` | `"site.mk"` |
| `getDomain("https://site.mk#about")` | `"site.mk"` |
| `getDomain("https://wwwsite.mk")` | `"wwwsite.mk"` (no dot, so not `www.`) |
| `getDomain("https://sub.www.site.mk")` | `"sub.www.site.mk"` (only a leading `www.`) |

## Common mistakes

| Symptom | Cause | Fix |
|---|---|---|
| Every test fails, Console shows `got undefined` | No `return`, or you used `console.log`/`alert` instead | `return` the value |
| `isStrongPassword` returns `true` too early | `return true` inside the loop | Set flags in the loop, decide after it |
| `"password1"` counted as strong | Flags combined with `\|\|` | `hasUpper && hasLower && hasDigit` |
| Spaces count as digits | `ch >= 0 && ch <= 9` (numbers) | `ch >= "0" && ch <= "9"` (strings) |
| Slug `"-hello-world-"` | Dash added when the group starts | `pending` flag + `result !== ""` (1.4) |
| Slug `"hello---world"` | Dash added for every symbol, not per group | One dash per group (flag) |
| Slug has capitals | Forgot `title = title.toLowerCase();` (it doesn't change `title` by itself) | Assign the result |
| Domain `"/site.mk"` | `slice(7)` used for `https://` | `slice(8)` for `https://` |
| Domain `"https://x.mk"` for `"HTTPS://x.mk"` | `startsWith` before `toLowerCase` | Lowercase first (step 1) |
| Domain loses its last letter | `slice(0, indexOf(...))` when `indexOf` returned `-1` | Handle `-1`, or use the loop version |
| `Uncaught ReferenceError: isUpper is not defined` | Helper not pasted into the answer field | Put helpers in the same `<script>` |

## Modern versions (optional; use one style per function)

| Aud way | Modern |
|---|---|
| `for (let i = 0; i < s.length; i++) { const ch = s[i]; ... }` | `for (const ch of s) { ... }` |
| 3 flags + loop | `p.length >= 8 && /[A-Z]/.test(p) && /[a-z]/.test(p) && /[0-9]/.test(p)` (**not in auds**) |
| `pending` loop | `t.toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-+\|-+$/g, "")` (**not in auds**) |
| `"OK " + label` | `` `OK ${label}` `` (Fundamentals slide 36) |

Don't use `new URL(url).hostname` for `getDomain`. It throws on `"courses.finki.ukim.mk"` because there's no protocol, and it doesn't strip `www.`.

---

Sources: IP_AV1.pdf, IP_AV2.pdf, *2 - JavaScript Fundamentals.pdf*, *IP_2025-2026.Javascript-functions.pdf* (string methods slides 46–52).
