def lcs_table(x: str, y: str):
    n, m = len(x), len(y)

    # build table (n+1) x (m+1)
    table = [[0 for _ in range(m+1)] for _ in range(n+1)]

    # track best match
    best_len = 0
    best_pos = (0, 0)

    # fill in DP table
    for r in range(1, n+1):
        for c in range(1, m+1):
            if x[r-1] == y[c-1]:
                table[r][c] = table[r-1][c-1] + 1
                if table[r][c] > best_len:
                    best_len = table[r][c]
                    best_pos = (r, c)
            else:
                table[r][c] = 0

    # reconstruct substring from x using end position
    r, c = best_pos
    substring = x[r-best_len:r]

    # pretty print grid with labels
    print("Lookup Table:")
    print("    " + "  ".join(y))  # header row
    for i in range(1, n+1):
        row_str = x[i-1] + " | " + "  ".join(str(table[i][j]) for j in range(1, m+1))
        print(row_str)

    print("\nLongest Common Substring:", substring)
    print("Length:", best_len)


# Example
a, b = "ABAB", "BABA"
lcs_table(a, b)
