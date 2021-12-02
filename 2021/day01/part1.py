print([sum(map(lambda a,b:a>b,x[1:],x[:-1])) for x in [[int(l) for l in open("input").read().splitlines()]]][0])

# with open("input", "r") as f:
#     lines = f.readlines()

# depths = [int(line.strip()) for line in lines]
# count = 0
# for i in range(1, len(depths)):
#     if depths[i] > depths[i-1]:
#         count += 1

# print(count)
