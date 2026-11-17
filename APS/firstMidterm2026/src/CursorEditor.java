import aps.*;

/*
 * Advanced 2: a string of keystrokes.
 *   letter, digit or space -> typed at the cursor
 *   '<' -> cursor one position left  (nothing if already at the start)
 *   '>' -> cursor one position right (nothing if already at the end)
 *   '#' -> delete the character left of the cursor (nothing if there is none)
 * Print the final text, or an empty line if it is empty.
 *
 * The text is a DLL of characters. "cursor" points to the node just LEFT of
 * the cursor (null = the cursor is at the very start). Every keystroke only
 * touches the nodes next to the cursor, so each one is O(1).
 */
public class CursorEditor {

    static String solve(String keys) {
        DLL<Character> text = new DLL<>();
        DLLNode<Character> cursor = null;

        for (int i = 0; i < keys.length(); i++) {
            char c = keys.charAt(i);

            if (Character.isLetterOrDigit(c) || c == ' ') {
                // type c right after the cursor, then the cursor sits after c
                if (cursor == null) {
                    text.insertFirst(c);
                    cursor = text.getFirst();
                } else {
                    text.insertAfter(c, cursor);
                    cursor = cursor.succ;
                }
            } else if (c == '<') {
                // one step left; at the start (null) there is nowhere to go
                if (cursor != null) cursor = cursor.pred;
            } else if (c == '>') {
                // one step right, if there is a character to the right
                if (cursor == null) {
                    if (text.getFirst() != null) cursor = text.getFirst();
                } else if (cursor.succ != null) {
                    cursor = cursor.succ;
                }
            } else if (c == '#') {
                // delete the character left of the cursor; the cursor moves to the one before it
                if (cursor != null) {
                    DLLNode<Character> before = cursor.pred;
                    text.delete(cursor);
                    cursor = before;
                }
            }
            // any other character is ignored
        }

        StringBuilder out = new StringBuilder();
        for (DLLNode<Character> p = text.getFirst(); p != null; p = p.succ) {
            out.append(p.element);
        }
        return out.toString();      // "" -> printed as an empty line
    }

    public static void main(String[] args) {
        String[] tests = {"helo<l", "cat#r", "ac<b>d", "abc<<#>d", "abc<<x", "ab<<<<c", "abc>>d", "abc#", "a#b#", "", "a b<<#"};
        String[] expected = {"hello", "car", "abcd", "bdc", "axbc", "cab", "abcd", "ab", "", "", " b"};
        for (int i = 0; i < tests.length; i++) {
            String got = solve(tests[i]);
            System.out.println((got.equals(expected[i]) ? "OK   " : "FAIL ") + "\"" + tests[i] + "\" -> \"" + got + "\"");
        }
    }
}
