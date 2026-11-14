# SDKI prep: UI patterns in jQuery (Lab 2 + Midterm 1)

Both old midterms (2017, 2021) are the same task: build a page from a text using **entry points / grid / pyramid / collapsible panels / hover tools / modal**, then name the pattern + why. Open book: copy the "Зошто се користи?" lines from the cheatsheet for theory. Game/timer stuff (`setInterval`, `.animate`) is NOT on the midterms; only practice it if tomorrow's lab is the squares game.

Setup: copy `Sabloni\jquery\jquery\` next to your html. Order: `jquery-ui.css`, `jquery.js`, `jquery-ui.js`, then your script. F12 Console open. Everything goes in `$(document).ready(function(){ ... });`.

---

# 1. jQuery you need (10 min)

| Need | Code |
|---|---|
| select | `$("#id")`, `$(".cls")`, `$("tag")` (no `#` = looks for a tag, finds 0, no error) |
| clicked element | `$(this)` inside `function(){}` (NOT arrow) |
| move around | `.find(".x")`, `.next()`, `.siblings(".x")`, `.closest(".box")`, `.parent()` |
| text / html / value | `.text(x)`, `.html(x)`, `.val()` |
| attribute | `.attr("title")`, `.attr("data-index")` |
| show / hide | `.show()`, `.hide()`, `.slideToggle()` |
| classes | `.addClass("a")`, `.removeClass("a")` (no dot!) |
| add element | `$("#grid").append("<div class='item'>..</div>")` |
| loop array | `$.each(data, function(i, item){ ... })` |
| events | `.click(fn)`, `.hover(inFn, outFn)`; for elements created by code: `$("#parent").on("click", ".child", fn)` |

---

# 2. Patterns, most important first

**Trigger words in the task -> pattern**

| Task says | Pattern |
|---|---|
| 3-4 elements, "no other significant content", click -> enter | **Clear Entry Points** |
| "матрица", "заеднички шаблон", "слична визуелна тежина" | **Grid of Equals** |
| catalog -> detail, prev/next, back to base | **Pyramid** |
| modules open/close on title click, several at once | **Collapsible panels** |
| ... only one at a time | **Accordion** |
| buttons only on mouse over | **Hover Tools** |
| click -> window, rest disabled | **Modal Panel** |

## 2.1 Collapsible panels (in BOTH midterms)
```html
<div class="collapse">
  <div class="title">Support</div>
  <div class="data"><ul><li>Drivers</li><li>Manuals</li></ul></div>
</div>
```
```css
.collapse .data { display: none; }
.collapse .title { cursor: pointer; font-weight: bold; }
```
```js
$(".collapse .title").click(function(){ $(this).siblings(".data").slideToggle(200); });
```
Nested module = put another `.collapse` inside a `.data`. Same one line works.
**Practice:** 3 panels (Delivery / Warranty / Service), open two at once, then nest one.

## 2.2 Hover Tools (in BOTH midterms)
```html
<div class="box">
  <div class="title">Phone 1
    <div class="buttons"><button>Add to cart</button><button>Rate</button></div>
  </div>
</div>
```
```css
.buttons { opacity: 0; }
.box.active .buttons { opacity: 1; }
```
```js
$(".box").hover(
    function(){ $(this).addClass("active"); },
    function(){ $(this).removeClass("active"); }
);
```
(Prof hovers `.buttons` and uses `.parent().parent()`; hovering the whole `.box` is simpler. Pure CSS alternative: `.box:hover .buttons { opacity: 1; }`, no JS.)
**Practice:** buttons invisible until hover; Add to cart increments a `Cart: N` counter.

## 2.3 Grid of Equals (in BOTH midterms)
```css
.grid { display: grid; grid-template-columns: repeat(3, 1fr); grid-auto-rows: 150px; gap: 10px; }
```
Every item identical structure: image (or colored div) + name + buttons. Prof used `float: left; width: calc(100%/3 - 10px)`; grid is the modern way.

## 2.4 Clear Entry Points
Prof's 2017 solution: a `<nav>` with 3 links to 3 separate html pages (no JS). Single-page version:
```html
<button title="dslr">DSLR</button> ...
<div id="container"><div id="dslr">..grid..</div><div id="compact">..</div></div>
```
```js
$("#container > div").hide();
$("button").click(function(){
    $("#container > div").hide();
    $("#" + $(this).attr("title")).show();
});
```

## 2.5 Modal Panel (2021 midterm)
```html
<div id="modal_div" title="Comment"><input id="input" type="text"></div>
```
```js
let current;                                   // which item opened it
$("#modal_div").dialog({
    autoOpen: false, modal: true,
    buttons: { OK: function(){
        $(current).append("<p>Rating: " + $("#input").val() + "</p>");
        $(this).dialog("close");
    } }
});
$(".comment").click(function(){ current = $(this).closest(".box"); $("#modal_div").dialog("open"); });
```
Needs jQuery UI js + css. Without the css there's no overlay.

## 2.6 Pyramid (2021 midterm)
```js
const data = [{label:"DJI", desc:".."}, {label:"Parrot", desc:".."}, {label:"Yuneec", desc:".."}];
let index = 0;
function showData(){ $("#title").text(data[index].label); $("#desc").text(data[index].desc); }

$.each(data, function(i, item){ $("#base").append("<li data-index='" + i + "'>" + item.label + "</li>"); });
$("#base").on("click", "li", function(){
    index = parseInt($(this).attr("data-index"));
    showData(); $("#base").hide(); $("#detail").show();
});
$("#next").click(function(){ index = (index + 1) % data.length; showData(); });
$("#prev").click(function(){ index = (index - 1 + data.length) % data.length; showData(); });
$("#top").click(function(){ $("#detail").hide(); $("#base").show(); });
```
Start with `$("#detail").hide();`.

## 2.7 Accordion (only if "one at a time")
```js
$("#accordion").accordion({ collapsible: true });   // <h3>Title</h3><div>text</div> repeated
```

---

# 3. Mock Lab 2 (no solution, ~60 min)

> Да се креира веб-страница за продавница за велосипеди. Иницијално се прикажани четири елементи: **Mountain**, **Road**, **City** и **Kids**, што нудат влез до содржините. Не е прикажана друга значајна содржина.
>
> Со клик на категорија, во нов, детален поглед, се прикажуваат велосипедите од таа категорија. Во овој поглед се овозможува движење низ соседните категории (претходна и следна) и враќање на почетниот поглед.
>
> Велосипедите се организирани во матрица и следат заеднички шаблон. Визуелната тежина е слична. За секој се прикажува име, цена и слика (може обоен div).
>
> Кога покажувачот ќе се позиционира над велосипед, се појавуваат копчињата „Add to cart“ и „Review“. Во остатокот од времето се невидливи. Со „Add to cart“ се зголемува бројачот „Cart: N“.
>
> Со клик на „Review“ се отвора прозорец со поле за оценка (1-5) и копче „Submit“. Додека е прикажан, сите други акции се оневозможени. Ако оценката не е број од 1 до 5: alert „Невалидна оценка“ и прозорецот останува отворен; инаку под велосипедот се испишува „Оценка: N“ и прозорецот се затвора.
>
> Се прикажуваат и модулите **Delivery**, **Warranty** и **Service**. Се отвораат и затвораат со клик на насловот. Може да се гледа повеќе од еден модул истовремено.
>
> **Дел 2:** За секое барање наведи го шаблонот и објасни зошто е соодветен.

**Order:** entry points (2.4) -> grid (2.3) -> pyramid prev/next/top (2.6) -> hover tools + cart (2.2) -> modal + validation (2.5) -> panels (2.1) -> Дел 2 from cheatsheet.

**Test:** only 4 entries at start; next from Kids -> Mountain; hover shows buttons; Cart counts across categories; rating `7`/`abc` -> alert and dialog stays; `4` -> `Оценка: 4` under the right bike; two panels open together.

---

# 4. Common mistakes

| Symptom | Fix |
|---|---|
| nothing happens, no error | selector typo (`$("grid")` instead of `$("#grid")`); check `$("#grid").length` in Console, 0 = wrong |
| new items don't react / aren't styled | handler/`.css` ran at load: use `.on("click", ".child", fn)` and put looks in CSS |
| `$ is not defined` / `.dialog is not a function` | wrong script order or missing jquery-ui.js |
| `$(this)` wrong | arrow function used: write `function(){}` |
| addClass does nothing | no dot: `addClass("active")` |
| rating under wrong item | save the item in a variable before opening the dialog (`current`) |
| dialog looks broken | copy the whole `jquery\` folder incl. `images\` |
