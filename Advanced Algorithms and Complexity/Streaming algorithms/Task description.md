## heavy_hitter
Nice vs Naughty. List 𝐴 is a sequence of integer tuples (𝑘𝑖, 𝑔𝑘𝑖), 𝑖 = 1, . . . , 𝑁, where for each child 𝑘𝑖, 𝑖 = 1, . . . , 𝑁 the
number of good things done by child with id 𝑘𝑖 throughout the year equals 𝑔𝑖. Similarly, list 𝐵 is a sequence
of integer tuples (𝑘𝑖, 𝑏𝑖), 𝑖 = 1, . . . , 𝑁, where for each child 𝑖 = 1, . . . , 𝑁 the number of good things done by
child with id 𝑘𝑖 throughout the year equals 𝑏𝑖. Adam first tells the number of children 𝑁, and the
positive integer threshold 1 ≤ 𝑡 ≤ 106 that he is interested in. Adam first reads list 𝐴 once, then
list 𝐵. After that he gives a small set of child ids 𝑘1, . . . , 𝑘𝑟, and asks which of the children
𝑘𝑖, 𝑖 = 1, . . . , 𝑟 were nice and which were naughty, i.e. for each 𝑖 whether 𝑔𝑘𝑖 − 𝑏𝑘𝑖 ≥ 𝑡 or 𝑔𝑘𝑖 − 𝑏𝑘𝑖 < 𝑡.
Memory Limit: 10MB (so using a map is not efficient here).