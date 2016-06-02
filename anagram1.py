import time

file = open("/Users/zangxiaoxue/step_google/STEP_GOOGLE/dictionary.txt",'r')
lines = file.readlines()
file.close()
dictionary = {}
for line in lines:
    line = line.rstrip()
    dic_str = line.lower()
    key = list(dic_str)
    key.sort()
    key = ''.join(key)
    #print(key)
    if key in dictionary:
        if dic_str not in dictionary[key]:
            dictionary[key].append(dic_str)
    else:
        dictionary[key] = [dic_str]

word = input("Please enter the word: ")
#start = time.time()
my_list = word.lower().split(' ')
my_list = list(''.join(my_list))
my_list.sort()
my_str = ''.join(my_list)
start = time.time()
combination = []
word_length = len(my_str)
get_bin = lambda x: ('{0:0'+str(word_length)+'b}').format(x)
for x in range(1,2**word_length):
    mask = [int(i) for i in get_bin(x)]
    mask = [bool(i) for i in mask]
    combination.append(''.join([i*j for (i,j) in zip(mask, my_list)]))

combination = list(set(combination))
combination.sort(key = len, reverse = True)

find = False


for my_str in combination:
    if my_str in dictionary.keys():
        if not find:
            max_length=len(my_str)
            find = True
        if len(my_str)<max_length:
            end = time.time()
            break
        print("the anagram is %s"%dictionary[my_str])
print('time for search is %f.'%(end-start))
if not find:
    print('no match')
