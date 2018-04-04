/***********************************************************
    poly.c -- 多項式の計算
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COMPLEX  1  /* 複素数を使わないなら 0 にする */
typedef enum {FALSE, TRUE} boolean;
#define odd(n) ((n) & 1)  /* 奇数か */

#define N_LETTER  4  /* 最大文字数 */

typedef long int coeftype;  /* 係数 (符号あり) */
typedef unsigned short int expotype;  /* 指数 (符号なし) */
typedef struct node_ {  /* ノード (多項式の一つの項) */
    expotype expo[N_LETTER];  /* 指数 */
    coeftype real;            /* 実部 */
    #if COMPLEX
        coeftype imag;        /* 虚部 */
    #endif
    struct node_ *next;       /* 次の項へのポインタ */
} node;

int table[26];  /* 各文字の位置 */
node *avail;  /* 未使用セルのリスト */
node *value[26];  /* 各文字に代入された多項式 */
char letter[N_LETTER];  /* 文字の表 */
unsigned int cells;  /* 使用中のセル数 */
unsigned int max_cells;  /* 最大使用セル数 */
int ch;        /* readch() の返す値 */
coeftype num;  /* readnum() の返す値 */

void error(char *message)  /* エラー処理 */
{
    fprintf(stderr, "\n%s\n%u 個のセル使用\n",
        message, max_cells);
    exit(1);
}

void readch(void)  /* 標準入力から文字 ch を読む */
{
    boolean comment = FALSE;

    do {
        if ((ch = getchar()) == EOF) return;
        putchar(ch);
        if (ch == '%') comment = TRUE;  /* % から行末までは注釈 */
        else if (ch == '\n') comment = FALSE;
    } while (comment || isspace(ch));  /* 空白は無視 */
}

void readnum(void)  /* 数を読む */
{
    num = ch - '0';
    while (readch(), isdigit(ch))
        num = num * 10 + (ch - '0');
}

node *new_node(void)  /* 新しいノードを作る */
{
    node *p;

    if (avail == NULL) {
        p = malloc(sizeof(node));
        if (p == NULL) error("メモリ不足");
    } else {
        p = avail;  avail = p->next;
    }
    if (++cells > max_cells) max_cells = cells;
    return p;
}

void dispose_node(node *p)  /* ノードを消す */
{
    p->next = avail;  avail = p;  cells--;
}

void dispose(node *p)  /* 多項式を消す */
{
    node *q;

    q = p;  cells--;
    while (q->next != NULL) {
        q = q->next;  cells--;
    }
    q->next = avail;  avail = p;
}

node *constant(  /* 定数 */
    coeftype re
    #if COMPLEX
        , coeftype im
    #endif
    )
{
    int i;
    node *p, *q;

    p = new_node();
    if (re != 0
        #if COMPLEX
            || im != 0
        #endif
                ) {
        q = new_node();
        q->real = re;
        #if COMPLEX
            q->imag = im;
        #endif
        for (i = 0; i < N_LETTER; i++) q->expo[i] = 0;
        p->next = q;  q->next = NULL;
    } else p->next = NULL;
    return p;
}

node *copy(node *p)  /* 多項式のコピー */
{
    int i;
    node *q, *r;

    q = r = new_node();
    while ((p = p->next) != NULL) {
        r = r->next = new_node();
        r->real = p->real;
        #if COMPLEX
            r->imag = p->imag;
        #endif
        for (i = 0; i < N_LETTER; i++)
            r->expo[i] = p->expo[i];
    }
    r->next = NULL;
    return q;
}

void change_sign(node *p)  /* 符号反転 */
{
    while ((p = p->next) != NULL) {
        p->real = -(p->real);
        #if COMPLEX
            p->imag = -(p->imag);
        #endif
    }
}

void differentiate(node *p)  /* 微分 */
{
    int j;
    expotype e;
    node *p1;

    if (! isalpha(ch)) error("文字がありません");
    j = table[toupper(ch) - 'A'];
    if (j < 0) error("微分できません");
    p1 = p;  p = p->next;
    while (p != NULL) {
        if ((e = p->expo[j]) != 0) {
            p->expo[j] = e - 1;
            p->real *= e;
            #if COMPLEX
                p->imag *= e;
            #endif
            p1 = p;  p = p->next;
        } else {
            p = p->next;  dispose_node(p1->next);
            p1->next = p;
        }
    }
}

#if COMPLEX
void complex_conjugate(node *p)  /* 複素共役 */
{
    while ((p = p->next) != NULL)
        p->imag = -(p->imag);
}
#endif

void add(node *p, node *q)  /* p := p + q;  q は消す */
{
    int i;
    expotype ep, eq;
    node *p1, *q1;

    p1 = p;  p = p->next;
    q1 = q;  q = q->next;  dispose_node(q1);
    while (q != NULL) {
        while (p != NULL) {
            for (i = 0; i < N_LETTER; i++) {
                ep = p->expo[i];  eq = q->expo[i];
                if (ep != eq) break;
            }
            if (ep <= eq) break;
            p1 = p;  p = p->next;
        }
        if (p == NULL || ep < eq) {
            p1->next = q;  p1 = q;  q = q->next;
            p1->next = p;
        } else {
            p->real += q->real;
            #if COMPLEX
                p->imag += q->imag;
            #endif
            if (p->real != 0
                #if COMPLEX
                    || p->imag != 0
                #endif
                                    ) {
                p1 = p;  p = p->next;
            } else {
                p = p->next;
                dispose_node(p1->next);
                p1->next = p;
            }
            q1 = q;  q = q->next;  dispose_node(q1);
        }
    }
}

node *multiply(node *x, node *y) /* x, y の積を返す. x, y は不変 */
{
    int i;
    expotype ep, eq;
    node *p, *p1, *q, *r, *z;

    r = new_node();  r->next = NULL;  q = NULL;
    while ((y = y->next) != NULL) {
        p1 = r;  p = p1->next;  z = x;
        while ((z = z->next) != NULL) {
            if (q == NULL) q = new_node();
            #if COMPLEX
                q->real = y->real * z->real - y->imag * z->imag;
                q->imag = y->real * z->imag + y->imag * z->real;
            #else
                q->real = y->real * z->real;
            #endif
            for (i = 0; i < N_LETTER; i++)
                q->expo[i] = y->expo[i] + z->expo[i];
            while (p != NULL) {
                for (i = 0; i < N_LETTER; i++) {
                    ep = p->expo[i];  eq = q->expo[i];
                    if (ep != eq) break;
                }
                if (ep <= eq) break;
                p1 = p;  p = p->next;
            }
            if (p == NULL || ep < eq) {
                p1->next = q;  p1 = q;  p1->next = p;
                q = NULL;
            } else {
                p->real += q->real;
                #if COMPLEX
                    p->imag += q->imag;
                #endif
                if (p->real != 0
                    #if COMPLEX
                        || p->imag != 0
                    #endif
                                        ) {
                    p1 = p;  p = p->next;
                } else {
                    p = p->next;
                    dispose_node(p1->next);
                    p1->next = p;
                }
            }
        }
    }
    if (q != NULL) dispose_node(q);
    return r;
}

node *power(node *x, expotype n) /* x の n 乗を返す. x は捨てる */
{
    node *p, *q;

    if (n == 1) return x;
    if (n == 0) {
        #if COMPLEX
            p = constant(1, 0);
        #else
            p = constant(1);
        #endif
    } else {
        p = multiply(x, x);  n -= 2;
        if (n > 0) {
            q = p;
            if (odd(n)) p = multiply(q, x);
            else        p = copy(q);
            dispose(x);  x = q;  n /= 2;
            if (odd(n)) {
                q = multiply(p, x);  dispose(p);  p = q;
            }
            while ((n /= 2) != 0) {
                q = multiply(x, x);  dispose(x);  x = q;
                if (odd(n)) {
                    q = multiply(p, x);  dispose(p);  p = q;
                }
            }
        }
    }
    dispose(x);
    return p;
}

void sincos(node *x)  /* p^2 + q^2 = 1 の処理 */
{
    int i;
    node *p, *p1, *q, *r, *s, *t;

    do {
        i = 0;  /* flag */
        p1 = x;  p = p1->next;
        q = r = new_node();
        s = t = new_node();
        while (p != NULL) {
            if (p->expo[1] >= 2) {
                r = r->next = new_node();
                r->real = -(p->real);
                #if COMPLEX
                    r->imag = -(p->imag);
                #endif
                r->expo[0] = p->expo[0] + 2;
                r->expo[1] = p->expo[1] -= 2;
                for (i = 2; i < N_LETTER; i++)
                    r->expo[i] = p->expo[i];  /* i≠0 になる */
                t = t->next = p;
                p1->next = p = p->next;
            } else {
                p1 = p;  p = p->next;
            }
        }
        if (i != 0) {
            r->next = t->next = NULL;
            add(x, q);  add(x, s);
        } else {
            dispose_node(q);  dispose_node(s);
        }
    } while (i);
}

node *expression(void);  /* 式 */

node *variable(void)  /* 変数 */
{
    int i, j;
    node *p;

    i = toupper(ch) - 'A';  j = table[i];
    if (j >= 0) {
        #if COMPLEX
            p = constant(1, 0);
        #else
            p = constant(1);
        #endif
        readch();
        if (ch == '^') {  /* ちょっとした最適化 */
            readch();
            if (! isdigit(ch)) error("数がありません");
            readnum();
        } else num = 1;
        (p->next)->expo[j] = (expotype) num;
    } else {
        if (value[i] == NULL) error("未定義の文字です");
        p = copy(value[i]);
        readch();
    }
    return p;
}

node *factor(void)  /* 因子 */
{
    node *p;

    if (ch == '(') {
        readch();  p = expression();
        if (ch != ')') error("')' がありません");
        readch();
    } else if (isdigit(ch)) {
        readnum();
        #if COMPLEX
            if (toupper(ch) != 'I') p = constant(num, 0);
            else {
                readch();  p = constant(0, num);
            }
        #else
            p = constant(num);
        #endif
    } else if (isalpha(ch)) p = variable();
    else error("因子の文法が間違っています");
    for ( ; ; ) {
        switch (ch) {
        case '^':
            readch();
            if (! isdigit(ch)) error("数がありません");
            readnum();  p = power(p, (expotype) num);
            break;
        case ':':
            readch();  differentiate(p);  readch();
            break;
        case '!':
            readch();  sincos(p);
            break;
        #if COMPLEX
        case '\'':
            readch();  complex_conjugate(p);
            break;
        #endif
        default:
            return p;
        }
    }
}

node *term(void)  /* 項 */
{
    node *p, *q, *r;

    p = factor();
    while (ch == '*') {
        readch();  q = p;  r = factor();
        p = multiply(q, r);
        dispose(q);  dispose(r);
    }
    return p;
}

node *expression(void)  /* 式 */
{
    node *p, *q;

    if (ch == '-') {
        readch();  p = term();  change_sign(p);
    } else {
        if (ch == '+') readch();
        p = term();
    }
    for ( ; ; ) {
        switch (ch) {
        case '+':
            readch();  q = term();  break;
        case '-':
            readch();  q = term();  change_sign(q);  break;
        default:
            return p;
        }
        add(p, q);
    }
}

void initialize(void)  /* 初期化 */
{
    int i;

    avail = NULL;  cells = max_cells = 0;
    for (i = 0; i < 26; i++) {
        table[i] = -1;  value[i] = NULL;
    }
}

void declare(void)  /* 文字宣言 */
{
    int i, j;

    for (i = 0; i < 26; i++) {
        table[i] = -1;
        if (value[i] != NULL) {
            dispose(value[i]);  value[i] = NULL;
        }
    }
    j = 0;  readch();
    while (isalpha(ch)) {
        i = toupper(ch) - 'A';
        if (table[i] < 0) {
            if (j >= N_LETTER) error("文字が多すぎます");
            table[i] = j;  letter[j] = ch;  j++;
        }
        readch();
        if (ch == ',') readch();
    }
}

void assign(void)  /* 代入 */
{
    int i;
    node *p;

    i = toupper(ch) - 'A';
    if (table[i] >= 0) error("左辺が間違っています");
    readch();
    if (ch != '=') error("'=' がありません");
    readch();  p = expression();
    if (value[i] != NULL) dispose(value[i]);
    value[i] = p;
}

#if COMPLEX

void print(void)  /* 式の印刷 (複素数版) */
{
    int i;
    boolean first, one;
    node *p, *q;
    coeftype re, im;
    expotype e;

    first = TRUE;  readch();  p = q = expression();
    printf("\n");
    while ((p = p->next) != NULL) {
        one = FALSE;
        re = p->real;  im = p->imag;
        if (im == 0) {
            if (re >= 0) {
                if (! first) printf(" + ");
            } else {
                printf(" - ");  re = -re;
            }
            if (re == 1) one = TRUE;
            else printf("%ld", (long int) re);
        } else if (re == 0) {
            if (im >= 0) {
                if (! first) printf(" + ");
            } else {
                printf(" - ");  im = -im;
            }
            printf("%ldi", (long int) im);
        } else {
            if (! first) printf(" + ");
            printf("(%ld%+ldi)",
                (long int) re, (long int) im);
        }
        first = FALSE;
        for (i = 0; i < N_LETTER; i++)
            if ((e = p->expo[i]) != 0) {
                if (! one) printf(" * ");
                one = FALSE;
                printf("%c", letter[i]);
                if (e != 1)
                    printf("^%lu",
                        (unsigned long int) e);
            }
        if (one) printf("1");
    }
    if (first) printf("0");
    printf("\n");
    dispose(q);
}

#else

void print(void)  /* 式の印刷 (実数版) */
{
    int i;
    boolean first;
    node *p, *q;
    coeftype c;
    expotype e;

    first = TRUE;  readch();  p = q = expression();
    printf("\n");
    while ((p = p->next) != NULL) {
        if ((c = p->real) >= 0) {
            if (! first) printf(" + ");
        } else {
            printf(" - ");  c = -c;
        }
        first = FALSE;
        if (c != 1) printf("%ld", (long int) c);
        for (i = 0; i < N_LETTER; i++)
            if ((e = p->expo[i]) != 0) {
                if (c != 1) printf(" * ");
                c = 0;
                printf("%c", letter[i]);
                if (e != 1)
                    printf("^%lu",
                        (unsigned long int) e);
            }
        if (c == 1) printf("1");
    }
    if (first) printf("0");
    printf("\n");
    dispose(q);
}

#endif

int main(void)
{
    printf("***** 簡単な多項式処理系 *****\n");
    initialize();
    while (readch(), ch != EOF) {
        if (ch == '@') declare();
        else if (ch == '?') print();
        else if (isalpha(ch)) assign();
        else error("illegal statement");
        if (ch != ';') error("';' がありません");
        printf("\n%u 個のセル使用 (%u 個使用中)\n",
            max_cells, cells);
        max_cells = cells;
    }
    return 0;
}
