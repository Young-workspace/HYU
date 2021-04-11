import sys              # for input parameter
from itertools import combinations      # To make combination

# save input parameters
min_support = float(sys.argv[1])/100
input_file = sys.argv[2]
output_file = sys.argv[3]

def read_file():
    # original data set
    items = []

    # open input file
    open_file = open(input_file, 'r')

    # read input file per row
    for line in open_file:
        # save item_id
        tmp = line.replace('\n', '')        # delete last enter '\n'
        tokens = tmp.split('\t')            # split with \t

        items.append(tokens)

    # close input file
    open_file.close()
    return items


# generate first frequent set  
def generate_first_frequent(items):
    C1 = dict()         # save first requent set

    for row in items:
        for item in row:
            # if item is not in C1 , add item and count 1
            if item not in C1.keys():       
                C1[item] = 1
            else:
                C1[item] += 1           # add count

    # return frequent sets
    return check_frequent(C1)


# check wheter data is frequent or not
def check_frequent(item_set):
    # minimum support * num_of_candidate
    min_support_cnt = min_support * len(item_set)

    # save checked data
    frequent_set = dict()

    # check if count >= min_support_cnt, if true, save it
    for key in item_set.keys():
        if item_set[key] >= min_support_cnt:
            frequent_set[key] = item_set[key]
    
    # if no frequent data, exit
    if len(frequent_set) < 1:
        return -1
    else:
        return frequent_set


# self joing to generate candidate
def self_join(length, prev_items):
    # Use combination to join
    join = convert_to_set(list(combinations(prev_items,2)))
    
    if length == 2:         # size of each item = 1, easy to combine
        return join     
    else:                   # size of each item > 1
        identical = []
        # find identical items 
        for items in prev_items:
            for each in items:
                if each not in identical:
                    identical.append(each)
        # self-join identical items
        result = convert_to_set(list(combinations(identical, length)))
        return result


# convert data type to set
def convert_to_set(element):
    tmp = []
    for item in element:
        tmp.append(set(item))
    return tmp


# Use prune self_joined set and scan DB
def pruning(length, original_DB, prev_items, candidate):
    frequent_set = dict()

    # Arpiroi Pruning principle
    if length == 2:             # all previous will be candidate
        for item in candidate:
            # add to frequent_set
            frequent_set[tuple(item)] = 0
    else:
        prev_items = convert_to_set(prev_items)
          
        for item in candidate:
            count  = 1
            comb_list = list(combinations(item, len(item)-1))          # list of combinations
            for l in comb_list:
                if set(l) not in prev_items:
                    count = 0
                    break
            if count == 1:
                # add to frequent_set
                frequent_set[tuple(item)] = 0
    
    # scan original DB, if key is subset of original DB, add 1 to count
    for key in frequent_set.keys():
        for row in original_DB:
            if set(key).issubset(set(row)):
                frequent_set[key] += 1

    # check whether frequent_set is frequent or not
    return check_frequent(frequent_set)


# Make association rule and return saved list
def generate_association(original, frequent_set):
    # Total number of transaction
    total = len(original)
    
    save = []
    for row in frequent_set[1:]:            # length of item in [0] is 1, so skip [0]
        # for each items in frequent_set
        for keys, freq in row.items():
            # save length of item
            length = len(keys)

            # loop to make n to 2 combinations
            while length > 1:
                # make combinations
                combi = list(combinations(keys, length-1))

                for item in combi:
                    item = set(item)
                    
                    # Get reverse set
                    reverse = set(keys) - set(item)

                    support = freq / total * 100
                    
                    count = 0
                    for ori in original:
                        if set(ori) >= item:
                            count += 1
                    confidence = freq / count * 100

                    # change to int
                    item = set(map(int, item))
                    reverse = set(map(int, reverse))

                    if support >= min_support * 100:
                        line = (str(item) + '\t' + str(reverse) + '\t' + 
                            str('%.2f' % round(support,2)) + '\t' + 
                            str('%.2f' % round(confidence,2)) + '\n')
                         
                        save.append(line)
                    length -= 1
            
    return save
  
        
# save result to txt file
def save_result(data):
    # open input file
    open_file = open(output_file, 'w')

    # write to file
    for line in data:
        open_file.write(line)

    # close input file
    open_file.close()


# apriori algorithm, item_set: original items
def apriori(item_set):
    # frequent data set 
    frequent_set = []

    # save first frequent set, item_length = 1
    frequent_set.append(generate_first_frequent(item_set))

    item_length = 2
    
    # loop until no candidate exist
    while True:
        # save previous frequent set
        pre_set = list(frequent_set[item_length - 2].keys())

        # Generate Candidate ( Self-Join + Pruning )
        join = self_join(item_length, pre_set)
        candidate = pruning(item_length, item_set, pre_set, join)

        if candidate == -1:
           break
        else:
            frequent_set.append(candidate)
            item_length += 1

    data = generate_association(item_set, frequent_set)
    return data


# main function 
if __name__ == "__main__":
    # open file and save data
    item_set = read_file()

    data = apriori(item_set)

    # open file and write data
    save_result(data)
