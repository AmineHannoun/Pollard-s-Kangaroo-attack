# Pollard-s-Kangaroo-attack
The goal of this exercise is to write a simple implementation of Pollard’s Kangaroo algo-
rithm to compute the discrete logarithm of a group element whose exponent is known to
lie in a “small” interval, without using (much) memory.
Let G = ⟨g⟩ be a finite group of order N, and h = ga, a ∈ J0, WK, W ≪ N, be an
element for which we want to compute the discrete logarithm a. The algorithm is based on
the sequence of jumps of two kangaroos: a tame kangaroo, that always knows the discrete
logarithm of the element it lands on; and a wild kangaroo, that can only remember the
jumps from its starting point.
Both kangaroos jump deterministically and identically from one group element to
another; in other words, both use the same jump map J : G → G. They also regularly lay
traps to try to catch each other, and it is clear that if one jumps on an element already
visited by the other, the former will eventually get caught by a trap of the latter (in other
words, barring a full cycle in the entire group, a kangaroo cannot get caught as long as it
is leading (i.e. has the largest logarithm)). When this happens, one has in fact recovered
enough information to compute the discrete logarithm of h.
In more details one does the following, where k, μ, d are parameters whose values are
to be determined later.
— Split G into k subsets Sj of approximately equal size; pick k exponents ej s.t. their
average 1/k Pk
j=1 ej ≈ μ; define J from the k partial maps Jj : Sj → G, x 7 → xgej .
1

— The tame kangaroo’s sequence (xn) is defined as x0 = g⌈W/2⌋ (i.e. the middle of
the interval); xi+1 = J(xi). Notice that at any time the discrete logarithm bi of
xi = gbi is known.
— The wild kangaroo’s sequence (yn) is defined as y0 = h; yi+1 = J(yi). Notice that
at any time, one can write yi as hgci where ci is known.
— Define D : G → {⊤, ⊥} so that Pr[D(x) = 1 : x ↞ G] = d; we say that the elements
for which D returns ⊤ are distinguished.
— Anytime a tame (resp. wild) kangaroo lands on a distinguished element xi (resp.
yi), it lays a trap by recording (xi, bi) (resp. (yi, ci)) in an efficient data structure
for sets. However, if a trap (yj, cj) (resp. (xj, bj)) was already present, it instead
gets trapped and returns the discrete logarithm |bi − cj| (resp. |bj − ci|).
A heuristic analysis (cf. [Gal12, §14.5]) suggests that for k ≈ log(W)/2, μ ≈ √W/2,
d ≈ log(W)/√W, the time cost of this algorithm is O(√W) group operations, and the
memory cost is “small”.
The objective is now for you to implement this algorithm to search for logarithms in
J0, 264 − 1K in the subgroup G < F×
2115−85 of prime order:
989008925435205262577237396041921 ≈ 2109.6
