#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100

typedef char Elemtype;
typedef struct TNode {
    Elemtype data;
    struct TNode *left;
    struct TNode *right;
} BTNode;

// ============ 括号表示法建树 ============
BTNode *CreateBT(char str[]) {
    BTNode *st[MaxSize];       // 栈：存"正在处理其孩子的结点"
    int top = -1;
    BTNode *root = NULL, *p = NULL;
    int k = 1;                 // 1: 下一个挂左边  2: 下一个挂右边
    char ch;

    for (int i = 0; (ch = str[i]) != '\0'; i++) {
        if (ch == '(') {
            st[++top] = p;     // 当前结点进栈
            k = 1;             // 先处理左孩子
        } else if (ch == ')') {
            top--;             // 这棵子树处理完，出栈
        } else if (ch == ',') {
            k = 2;             // 左孩子结束，下一个是右孩子
        } else {               // 字母：新建结点
            p = (BTNode *)malloc(sizeof(BTNode));
            p->data = ch;
            p->left = p->right = NULL;
            if (root == NULL) {
                root = p;      // 第一个结点是根
            } else {
                if (k == 1) st[top]->left = p;
                else        st[top]->right = p;
            }
        }
    }
    return root;
}

// 求树高（层数）
int Height(BTNode *b) {
    if (b == NULL) return 0;
    int lh = Height(b->left);
    int rh = Height(b->right);
    return (lh > rh ? lh : rh) + 1;
}

// ============ 循环队列（存结点指针，允许 NULL） ============
typedef struct {
    BTNode *data[MaxSize];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue *&Q) {
    Q = (SqQueue *)malloc(sizeof(SqQueue));
    Q->front = Q->rear = 0;
}

bool EnQueue(SqQueue *Q, BTNode *e) {
    if ((Q->rear + 1) % MaxSize == Q->front) return false;
    Q->rear = (Q->rear + 1) % MaxSize;
    Q->data[Q->rear] = e;
    return true;
}

bool DeQueue(SqQueue *Q, BTNode *&e) {
    if (Q->front == Q->rear) return false;
    Q->front = (Q->front + 1) % MaxSize;
    e = Q->data[Q->front];
    return true;
}

int QueueLength(SqQueue *Q) {
    return (Q->rear - Q->front + MaxSize) % MaxSize;
}

// ============ 核心：树状打印 ============
void PrintTree(BTNode *b) {
    if (b == NULL) return;
    int H = Height(b);
    SqQueue *Q;
    InitQueue(Q);
    EnQueue(Q, b);

    for (int lv = 0; lv < H; lv++) {
        int h    = H - 1 - lv;
        int lead = (1 << h) - 1;
        int gap  = (1 << (h + 1)) - 1;
        int count = QueueLength(Q);

        for (int i = 0; i < lead; i++) printf(" ");

        for (int k = 0; k < count; k++) {
            BTNode *p;
            DeQueue(Q, p);
            if (p != NULL) {
                printf("%c", p->data);
                EnQueue(Q, p->left);
                EnQueue(Q, p->right);
            } else {
                printf(" ");
                EnQueue(Q, NULL);
                EnQueue(Q, NULL);
            }
            if (k != count - 1) {
                for (int i = 0; i < gap; i++) printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    SetConsoleOutputCP(65001);
    char s[] = "A(B(D(,G)),C(E,F))";
    BTNode *root = CreateBT(s);
    printf("树高：%d\n", Height(root));
    PrintTree(root);
    return 0;
}