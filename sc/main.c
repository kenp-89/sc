/*
 *  main.c
 *  sc - subset counter
 *
 *  Created by Ken Peck on 11/9/14.
 *  Copyright (c) 2014 com.kpp. All rights reserved.
 *
 *  (I believe this to be the correct answer to Problem G
 *  at the 2014 ICPC.)
 */

#include <stdlib.h>
#include <stdio.h>

#define MINN 1
#define MAXN 30

static uint64_t nCrexec = 0;

uint64_t fact(int64_t x) {
    if (x == 0)
        return 1;
    if (x < 0) {
        fprintf(stderr, "sc: fact(%lld): cannot use integers less than 0\n", x);
        exit(1);
    }

    return (x *= fact(x-1));
}

/* only for debugging fact() */
void facttest(int caseN) {
    int i;
    uint64_t x;
    printf("Entering facttest:\n");
    for (i = 1; i <= caseN; i++) {
        printf("Enter an integer: ");
        scanf("%llu", &x);
        printf("Case %d: %llu\n", i, fact(x));
    }
    return;
}

uint64_t nCr(int n, int r) {
    ++nCrexec;
    int i;
    uint64_t m = 1;
    if (n < r)
        return 0;
    if (n == r + 1)
        return n;
    if (r == 1)
        return n;
    /*
     * We should simplify before computing factorials.
     * Let's do that here.
     * --------------------
     * Method #1
     * Case #1
     * This method will execute (2^N)-1 times,
     * where N = n-29.
     * This is the Tower of Hanoi solution.
     * Occurs when (? < r < ?)
     * Case #2
     * ...TODO
     * Thus, we have a VERY slow algorithm.
     * Try to think of a faster way to do this.
     * Maybe work backwards??
     */
    if (n >= 30) {
        return (nCr(n-1,r-1) + nCr(n-1,r));
    }
    
    /* Method #2 */
    if (r > (n-r)) {
        for (i = n; i > r; i--)
            m *= i;
        return (m/(fact(n-r)));
    }
    else {
        for (i = n; i > (n-r); i--)
            m *= i;
        return (m/fact(r));
    }

}

/* for debugging nCr() */
void nCrtest(int caseN) {
    int i;
    int n, r;
    printf("Entering nCrtest:\n");
    for (i = 1; i <= caseN; i++) {
        nCrexec = 0;
        printf("Enter your n and your r: ");
        scanf("%d %d", &n, &r);
        printf("Case %d: %llu\n", i, nCr(n,r));
        printf("cycles: %llu\n", nCrexec);
    }
    
    return;
}

/*
 *  This is a (REALLY BUGGY) test mode used to test
 *  the nCr and fact functions for correct answers with
 *  user-supplied sample data.
 */
void dbg() {
    char v = 0;
    int caseN;
    printf("Entering test mode...\n"
           "Type the mode followed by the number of trials.\n"
           "Enter 'f' for factorials.\n"
           "Enter 'c' for combinations.\n"
           "Enter 'q' to quit.\n");
    while (v != 'q') {
        v = 0;
        printf("sc> ");
        scanf(" %c", &v);
        /* insert conditionals here */
        if (v == 'f') {
            printf("Number of trials: ");
            scanf(" %d", &caseN);
            facttest(caseN);
        }
        else if (v == 'c') {
            printf("Number of trials: ");
            scanf(" %d", &caseN);
            nCrtest(caseN);
        }
    }
    
    return;
}

int main(int argc, const char * argv[]) {
    int caseN, i, err;
    int n, k; /* n: number of sets; k: size of subsets */
    uint64_t result;
    
    scanf("%d", &caseN);
    
    if (caseN < 1) {
        dbg();
        goto finish;
    }
    
    for (i = 1; i <= caseN; i++) {
        err = 0;
        scanf("%d %d", &n, &k);
        
        /* error checking routines: not required for solution */
        if (n < MINN) {
            err = 1;
            fprintf(stderr, "sc: n must be at least %d.\n", MINN);
        }
        else if (n > MAXN) {
            err = 1;
            fprintf(stderr, "sc: n must be no greater than %d.\n", MAXN);
        }
        if (k < 1) {
            err = 1;
            fprintf(stderr, "sc: k must be at least 1.\n");
        }
        else if (k > n) {
            err = 1;
            fprintf(stderr, "sc: k cannot be greater than n.\n");
        }
        if (err)
            goto skip;
        /* end error checking. */
        if (n == k)
            result = n;
        else
            result = nCr(n, k);
        printf("Case %d: %llu\n", i, result);
    skip:;
    }
finish:
    return 0;
}
