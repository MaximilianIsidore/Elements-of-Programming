def count_bits(n):
    numbits = 0

    while (n):
        numbits += (n & 1)
        n = n>>1
    
    return numbits

print(count_bits(15))