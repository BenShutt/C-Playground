# Triangle Numbers

This problem arose from a mobile app project where a UI was organized into a triangular grid.
There is a comparatively simple iterative workaround, but it is interesting to explore the purist mathematical solution.

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

We want to find the function that maps any number to its corresponding row and column.

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

## Formally

Define $\mathbb{N} = \{ 1, 2, 3, \ldots, \infty \}$. We want to find the function $f \colon \mathbb{N} \to \mathbb{N}^2$ such that $\forall n \in \mathbb{N}$ $\exists i, j \in \mathbb{N}^{2}$ so that

$$f(n)=(i,j)$$

## Solution

Denote the $ith$ triangle number with

$$T_{i} = \frac{1}{2} i (i+1)$$

$\forall n \in \mathbb{N}$ there must be a row, $i$, in which it resides. Since the last column of any row is a triangle number, the number $n$ must be (strictly) greater than the triangle number of the previous row and less than or equal to the triangle number of the current row.

$$T_{i-1} < n \leq T_{i}$$

which expanded is equivalent to

$$\frac{1}{2} (i-1) i < n \leq \frac{1}{2} i (i+1)$$

This gives us two inequalities to solve. Consider first the left $<$ case

$$\frac{1}{2} (i-1) i < n$$

Completing the square and multiplying by a positive factor gives

$$\left(i - \frac{1}{2} \right)^{2} < \frac{8n + 1}{4}$$

Since $\sqrt{x}$ is monotonically increasing, $n \geq 1$, and $\sqrt{8n + 1} \geq 3$ we must take the positive root. This results in

$$i < \frac{1 + \sqrt{8n + 1}}{2}$$

Following similar logic for the other inequality we acquire

$$\frac{-1 + \sqrt{8n + 1}}{2} \leq i < \frac{1 + \sqrt{8n + 1}}{2}$$

Since the left hand side is precisely $1$ less than the right hand side, $i$ must be the (single) integer between these two values. Given the left hand side could be equal to we have

$$i=\Bigg\lceil\frac{-1 + \sqrt{8n + 1}}{2}\Bigg\rceil$$

The column can be determined from the row, $i$, and number, $n$, with

$$j = n + i - T_{i}$$

or equally

$$j = n - T_{i-1}$$

## Notes

* On Github, the `\{` and `\}` for curly brackets doesn't seem to render.
* The "following similar logic" for the less than or equal to expression is pretty loose - the jump needs to be clearer.
