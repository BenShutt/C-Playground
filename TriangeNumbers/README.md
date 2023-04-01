# Triangle Numbers

This problem arose from a mobile app project where a UI was organized into a triangular grid.
There is a comparatively simple iterative workaround, but it is interesting to explore the more efficient, purist mathematical solution.

## The Problem

Consider a triangular grid of numbers

```
1
2 3
4 5 6
7 8 9 10
...
```

These numbers can be expressed as 2D (row, column) grid coordinates like

```
(1, 1)
(2, 1) (2, 2)
(3, 1) (3, 2) (3, 3)
(4, 1) (4, 2) (4, 3) (4, 4)
...
```

We want to determine the function that maps any number to its corresponding row and column.

## Examples

```
1 → (1, 1)
2 → (2, 1)
3 → (2, 2)
4 → (3, 1)
5 → (3, 2)
6 → (3, 3)
...
```

## Expressed Formally

Define $\N=\{1,2,3,\ldots,\infty\}$. Then $\forall n\in\N$ we want to find the function $f\colon\N\to\N^2$ and $i,j\in\N^{2}$ so that

$$f(n)=(i,j)$$

## Solution

Denote the $ith$ triangle number with

$$T_i=\frac{1}{2}i(i+1)$$

We observe that, for row $i$, that $\forall n\in\N$ it follows

$$T_{i-1}<n\leq T_{i}$$

expanding $T_i$ yields

$$\frac{1}{2}(i-1)i<n\leq\frac{1}{2}i(i+1)$$

Since the last column of any row is a triangle number, the number $n$ must be (strictly) greater than the triangle number of the previous row and less than or equal to the triangle number of the current row.

This gives us two inequalities to solve. Consider the left $<$ case

$$\frac{1}{2}(i-1)i<n$$

Completing the square and multiplying by a positive factor gives

$$\left(i-\frac{1}{2}\right)^2<\frac{8n+1}{4}$$

Since $\sqrt{x}$ is monotonically increasing and $\sqrt{8n+1}\geq3$ we must take the positive root resulting in

$$i<\frac{1+\sqrt{8n+1}}{2}$$

Following similar logic for the other inequality we acquire

$$\frac{-1+\sqrt{8n+1}}{2}\leq i<\frac{1+\sqrt{8n+1}}{2}$$

Since the left hand side is precisely $1$ less than the right hand side, $i$ must be the (single) integer between these two values. Since the left hand side could be equal to we have

$$i=\Bigg\lceil\frac{-1+\sqrt{8n+1}}{2}\Bigg\rceil$$

The column can be determined by the remaining elements to this row's triangle number

$$j=i+n-T_i$$