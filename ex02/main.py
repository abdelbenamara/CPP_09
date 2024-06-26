import random


class PmergeMe:

    @staticmethod
    def _binary_search(value: int, s: list[int], size: int) -> int:
        left: int = 0
        right: int = size - 1
        idx: int = right // 2

        while left <= right:
            if s[idx] < value:
                left = idx + 1
            elif s[idx] > value:
                right = idx - 1
            else:
                break

            if right < 0:
                return 0

            idx = (left + right) // 2

        return idx + 1

    @staticmethod
    def merge_insert_sort(s: list[int], pairs: list[list[int]] = None, size: int = -1):
        if not pairs:
            pairs = []
            size = len(s)

        if size <= 0:
            return

        even: bool = size % 2 == 0
        limit: int = size // 2

        # print(f'Inputs\t\t: {s}')

        if not even:
            pairs.insert(0, [s.pop(0)])

        for i in range(limit):
            pairs.insert(0, [s.pop(0), s.pop(0)])

        # print(f' Step 1\t\t: {tmp}')

        for i in range(limit):
            if pairs[i][0] > pairs[i][1]:
                pairs[i].append(pairs[i].pop(0))

        # print(f'  Step 2\t: {pairs}')

        for i in range(limit):
            s.append(pairs[i][1])

        if limit > 1:
            PmergeMe.merge_insert_sort(s, pairs, limit)

        # print(f'   Step 3\t: {s}, {pairs}')

        for i in range(limit):
            for j in range(i, limit):
                if s[i] == pairs[j][1]:
                    pairs.insert(i, pairs.pop(j))

                    break

        s.insert(0, pairs.pop(0)[0])

        # print(f'    Step 4\t: {s}, {pairs}')

        e: int = 2
        pos: int = limit
        limit *= 2
        j = 2

        if even:
            limit -= 1

        while pos < limit:
            end: int = min(j, limit - pos)

            for i in reversed(range(end)):
                s.insert(PmergeMe._binary_search(
                    pairs[i][0], s, pos + end - i), pairs.pop(i)[0])

            pos += j
            j = pow(2, e) - j
            e += 1

        # print(f'     Step 5\t: {s}')


if __name__ == '__main__':
    x = []
    PmergeMe.merge_insert_sort(x)
    print(x)
    print('--------------------------------------------------')
    x = [9, 2, 5, 8, 1, 7, 3, 6, 4]
    PmergeMe.merge_insert_sort(x)
    print(x)
    print('--------------------------------------------------')
    x = [7, 2, 0, 5, 8, 1, 9, 3, 6, 4]
    PmergeMe.merge_insert_sort(x)
    print(x)
    print('--------------------------------------------------')
    x = [7, 2, 0, 5, 8, 14, 27, 22, 20, 29, 1, 9, 3, 6, 4]
    PmergeMe.merge_insert_sort(x)
    print(x)
    print('--------------------------------------------------')
    x = [17, 12, 10, 15, 18, 11, 19, 13, 16, 14, 27, 22, 20, 25, 28, 21, 29, 23, 26, 24, 7, 2, 0, 5, 8, 1, 9, 3, 6, 4]
    PmergeMe.merge_insert_sort(x)
    print(x)
    print('--------------------------------------------------')
    x = list(range(100000))
    random.shuffle(x)
    x = x[:3000]
    expected = sorted(x[:])
    print(f'first: {x[0]}, last: {x[-1]}, sorted: {x == expected}')
    PmergeMe.merge_insert_sort(x)
    print(f'first: {x[0]}, last: {x[-1]}, sorted: {x == expected}')
