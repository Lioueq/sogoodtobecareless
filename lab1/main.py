def radix_sort_lsd(nums):
    max_num = max(nums) if nums else 0
    max_bits = max_num.bit_length() if max_num > 0 else 1
    
    for bit in range(max_bits):
        mask = 1 << bit  # Маска для текущего бита (0b1, 0b10, 0b100, ...)
        bin_m = bin(mask)
        buckets = [[], []]  # 0 и 1
        
        for num in nums:
            bin_n = bin(num)
            buckets[(num & mask) != 0].append(num)
        
        nums = buckets[0] + buckets[1]
    
    return nums


def radix_sort_grouped(nums, group_size=2):
    max_num = max(nums) if nums else 0
    max_bits = max_num.bit_length() if max_num > 0 else 1
    
    for shift in range(0, max_bits, group_size):
        t = 1 << group_size
        buckets = [[] for _ in range(t)]
        mask = (1 << group_size) - 1
        bin_m = bin(mask)
        
        for num in nums:
            bucket_idx = (num >> shift) & mask
            buckets[bucket_idx].append(num)
        
        nums = [num for bucket in buckets for num in bucket]
    
    return nums


a = list(map(int, ['15', '13', '63', '32']))
a = radix_sort_lsd(a)

print(a)