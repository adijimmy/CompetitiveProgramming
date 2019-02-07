
// https://www.codechef.com/problems/IIITBH
package com.adijimmy;

import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.InputMismatchException;


class Node {
    public int value;
    public int[] left;
    public int[] right;

    public Node(int n) {
        left = new int[n];
        right = new int[n];
    }
}

public class Main {

    static final long mod = (int) 1e9 + 7;

    static void build(Node[] tree, int[] a, int left, int right, int idx) {
        if (left == right) {
            tree[idx].left[a[left]] = left;
            tree[idx].right[a[left]] = left;
            tree[idx].value = a[left];
        } else {
            int mid = (left + right) / 2;
            build(tree, a, left, mid, 2 * idx + 1);
            build(tree, a, mid + 1, right, 2 * idx + 2);
            for (int i = 1; i < 51; i++) {
                tree[idx].left[i] = Math.min(tree[2 * idx + 1].left[i], tree[2 * idx + 2].left[i]);
                tree[idx].right[i] = Math.max(tree[2 * idx + 1].right[i], tree[2 * idx + 2].right[i]);
            }
            int val = -1;
            int diff = -1;
            for (int i = 1; i < 51; i++) {
                if (diff < tree[idx].right[i] - tree[idx].left[i]) {
                    diff = tree[idx].right[i] - tree[idx].left[i];
                    val = i;
                }
            }
            tree[idx].value = val;
        }
    }

    static void update(Node[] tree, int left, int right, int pos, int value, int idx) {
        if (pos < left || right < pos) {
            return;
        }
        if (left == right) {
            for (int i = 1; i < 51; i++) {
                tree[idx].left[i] = 999999;
                tree[idx].right[i] = -1;
            }
            tree[idx].left[value] = pos;
            tree[idx].right[value] = pos;
            tree[idx].value = value;
        } else {
            int mid = (left + right) / 2;
            update(tree, left, mid, pos, value, 2 * idx + 1);
            update(tree, mid + 1, right, pos, value, 2 * idx + 2);
            for (int i = 1; i < 51; i++) {
                tree[idx].left[i] = Math.min(tree[2 * idx + 1].left[i], tree[2 * idx + 2].left[i]);
                tree[idx].right[i] = Math.max(tree[2 * idx + 1].right[i], tree[2 * idx + 2].right[i]);
            }
            int val = -1;
            int diff = -1;
            for (int i = 1; i < 51; i++) {
                if (diff < tree[idx].right[i] - tree[idx].left[i]) {
                    diff = tree[idx].right[i] - tree[idx].left[i];
                    val = i;
                }
            }
            tree[idx].value = val;
        }
    }

    static Node query(Node[] tree, int left, int right, int idx, int start, int end) {
        if (right < start || left > end) {
            Node res = new Node(51);
            for (int i = 1; i < 51; i++) {
                res.left[i] = 999999;
                res.right[i] = -1;
            }
            res.value = -1;
            return res;
        }
        if (left >= start && right <= end) {
            Node res = new Node(51);
            for (int i = 1; i < 51; i++) {
                res.left[i] = tree[idx].left[i];
                res.right[i] = tree[idx].right[i];
            }
            res.value = tree[idx].value;
            return res;
        }
        int mid = (left + right) / 2;
        Node L = query(tree, left, mid, 2 * idx + 1, start, end);
        Node R = query(tree, mid + 1, right, 2 * idx + 2, start, end);

        Node res = new Node(51);
        for (int i = 1; i < 51; i++) {
            res.left[i] = Math.min(L.left[i], R.left[i]);
            res.right[i] = Math.max(L.right[i], R.right[i]);
        }
        int val = -1;
        int diff = -1;
        for (int i = 1; i < 51; i++) {
            if (diff < res.right[i] - res.left[i]) {
                diff = res.right[i] - res.left[i];
                val = i;
            }
        }
        res.value = val;
        return res;
    }

    static void solve() {
        final InputReader in = new InputReader(System.in);
        final PrintWriter out = new PrintWriter(System.out);
        final long startTime = System.currentTimeMillis();

        int n = in.nextInt();
        int q = in.nextInt();

        int[] a = in.nextIntArray(n);
        Node[] tree = new Node[4 * n + 10];
        for (int i = 0; i <= 4 * n; i++) {
            tree[i] = new Node(51);
            tree[i].value = -1;
            for (int j = 1; j < 51; j++) {
                tree[i].left[j] = 999999;
                tree[i].right[j] = -1;
            }
        }
        build(tree, a, 0, n - 1, 0);
        while (q-- > 0) {
            int type = in.nextInt();
            if (type == 2) {
                int l = in.nextInt();
                int r = in.nextInt();
                Node ans = query(tree, 0, n - 1, 0, l - 1, r - 1);
                out.println(ans.value);
            } else {
                int pos = in.nextInt();
                int val = in.nextInt();
                update(tree, 0, n - 1, pos - 1, val, 0);
            }
        }

        long runningTime = System.currentTimeMillis() - startTime;
        System.err.println("Running duration: " + runningTime + " ms");
        out.close();
    }

    public Main() throws Exception {
        solve();
    }

    public static void main(String[] args) {
        new Thread(null, new Runnable() {
            @Override
            public void run() {
                try {
                    new Main();
                } catch (Exception e) {
                    e.printStackTrace();
                } catch (StackOverflowError e) {
                    System.out.println("RTE");
                }
            }
        }, "solve-thread-1", 1 << 26).start();
    }

    /**
     * Calculate a power b
     * and take a modulus with it to return the remainder obtained
     *
     * @param a   is the base
     * @param b   is the exponent
     * @param mod is the modulus value with which to take remainder
     * @return a^b % mod
     */
    static long power(long a, long b, long mod) {
        long res = 1L;
        while (b > 0) {
            if ((b & 1) == 1) {
                res = (res * a) % mod;
            }
            a = (a * a) % mod;
            b >>= 1;
        }
        return res;
    }

    static long inverse(long a) {
        return power(a, mod - 2, mod);
    }

    static long add(long a, long b) {
        return (a + b) % mod;
    }

    static long sub(long a, long b) {
        a -= b;
        a %= mod;
        if (a < 0) {
            a += mod;
        }
        return a;
    }

    static long mul(long a, long b) {
        return (a * b) % mod;
    }

    static class InputReader {

        private final InputStream stream;
        private final byte[] buf = new byte[8192];
        private int curChar, snumChars;
        private SpaceCharFilter filter;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int getNextByte() {
            if (snumChars == -1) {
                throw new InputMismatchException();
            }
            if (curChar >= snumChars) {
                curChar = 0;
                try {
                    snumChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (snumChars <= 0) {
                    return -1;
                }
            }
            return buf[curChar++];
        }

        public int nextInt() {
            int c = getNextByte();
            while (isSpaceChar(c)) {
                c = getNextByte();
            }
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = getNextByte();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9') {
                    throw new InputMismatchException();
                }
                res *= 10;
                res += c - '0';
                c = getNextByte();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public long nextLong() {
            int c = getNextByte();
            while (isSpaceChar(c)) {
                c = getNextByte();
            }
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = getNextByte();
            }
            long res = 0;
            do {
                if (c < '0' || c > '9') {
                    throw new InputMismatchException();
                }
                res *= 10;
                res += c - '0';
                c = getNextByte();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public int[] nextIntArray(int n) {
            int a[] = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = nextInt();
            }
            return a;
        }

        public long[] nextLongArray(int n) {
            long[] a = new long[n];
            for (int i = 0; i < n; i++) {
                a[i] = nextLong();
            }
            return a;
        }

        public String readString() {
            int c = getNextByte();
            while (isSpaceChar(c)) {
                c = getNextByte();
            }
            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = getNextByte();
            } while (!isSpaceChar(c));
            return res.toString();
        }

        public String nextLine() {
            int c = getNextByte();
            while (isSpaceChar(c)) {
                c = getNextByte();
            }
            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = getNextByte();
            } while (!isEndOfLine(c));
            return res.toString();
        }

        public boolean isSpaceChar(int c) {
            if (filter != null) {
                return filter.isSpaceChar(c);
            }
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        private boolean isEndOfLine(int c) {
            return c == '\n' || c == '\r' || c == -1;
        }

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);
        }
    }
}





