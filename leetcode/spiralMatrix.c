#include <stdio.h>
#include <stdlib.h>

// Simulation on a 3x4 matrix, showing how top/bottom/left/right shrink inward:
//
//   1   2   3   4
//   5   6   7   8
//   9  10  11  12
//
// Start: top=0 bottom=2 left=0 right=3   (top<=bottom && left<=right -> loop runs)
//
// --- iteration 1 ---
// right pass (row=top=0, cols left..right):  1 2 3 4        -> top becomes 1
// down  pass (col=right=3, rows top..bottom): 8 12          -> right becomes 2
// left  pass (row=bottom=2, cols right..left): 11 10 9      -> bottom becomes 1
// up    pass (col=left=0, rows bottom..top): 5              -> left becomes 1
//
//   [1] [2] [3] [4]
//   (5)  6   7  [8]
//  [9] (10)(11)[12]
//
//   [ ] = right pass    ( ) = down/left pass    already-visited border shown
//
// Boundaries are now: top=1 bottom=1 left=1 right=2
// Still top<=bottom (1<=1) and left<=right (1<=2) -> loop runs again
//
// --- iteration 2 ---
// right pass (row=top=1, cols 1..2):  6 7                   -> top becomes 2
// down  pass (rows top(2)..bottom(1)): none, top>bottom already, loop body skipped
//                                                            -> right becomes 1
// if(top<=bottom): 2<=1 false -> left pass skipped, bottom stays 1
// if(left<=right): 1<=1 true  -> up pass (rows bottom(1)..top(2)): none, 1<2 -> skipped
//                                                            -> left becomes 2
//
// Boundaries now: top=2 bottom=1 left=2 right=1
// top<=bottom fails (2<=1) -> outer while ends
//
// Final order: 1 2 3 4 8 12 11 10 9 5 6 7   (all 12 cells, no repeats)
//
// The two "if" guards before the left/up passes exist exactly for cases like
// iteration 2 above: once top/bottom (or left/right) cross, a naive 4th/3rd
// pass would re-walk a row/column already fully consumed by an earlier pass
// in the SAME iteration. This matters most for matrices that are a single
// row or a single column, where without the guards the left/up loops would
// re-emit values already emitted by the right/down loops.

int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize)
{
    int currIndex = 0;

    int top = 0;
    int bottom = matrixSize - 1;
    int left = 0;
    int right = matrixColSize[0] - 1;

    int *returnArr = (int *)malloc(matrixSize * matrixColSize[0] * sizeof(int));

    while (top <= bottom && left <= right)
    {
        for (int i = left; i <= right; i++) //---->
        {
            returnArr[currIndex] = matrix[top][i];
            currIndex += 1;
        }
        top++;

        for (int j = top; j <= bottom; j++) // down
        {
            returnArr[currIndex] = matrix[j][right];
            currIndex += 1;
        }
        right--;

        if (top <= bottom)
        {
            for (int i = right; i >= left; i--) //<-----
            {
                returnArr[currIndex] = matrix[bottom][i];
                currIndex += 1;
            }
            bottom--;
        }

        if (left <= right)
        {
            for (int i = bottom; i >= top; i--) // up
            {
                returnArr[currIndex] = matrix[i][left];
                currIndex += 1;
            }
            left++;
        }
    }

    *returnSize = matrixSize * matrixColSize[0];
    return returnArr;
}

static int **buildMatrix(int rows, int cols, int *colSizeOut)
{
    int **m = (int **)malloc(rows * sizeof(int *));
    int val = 1;

    for (int r = 0; r < rows; r++)
    {
        m[r] = (int *)malloc(cols * sizeof(int));
        for (int c = 0; c < cols; c++)
        {
            m[r][c] = val++;
        }
        colSizeOut[r] = cols;
    }

    return m;
}

int main(void)
{
    int colSize3x3[3];
    int **m3x3 = buildMatrix(3, 3, colSize3x3);
    int size3x3 = 0;
    int *r3x3 = spiralOrder(m3x3, 3, colSize3x3, &size3x3);
    printf("3x3 expected=1 2 3 6 9 8 7 4 5 got=");
    for (int i = 0; i < size3x3; i++) printf("%d ", r3x3[i]);
    printf("\n");

    int colSize3x4[3];
    int **m3x4 = buildMatrix(3, 4, colSize3x4);
    int size3x4 = 0;
    int *r3x4 = spiralOrder(m3x4, 3, colSize3x4, &size3x4);
    printf("3x4 expected=1 2 3 4 8 12 11 10 9 5 6 7 got=");
    for (int i = 0; i < size3x4; i++) printf("%d ", r3x4[i]);
    printf("\n");

    return 0;
}
