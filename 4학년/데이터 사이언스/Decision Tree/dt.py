import math
import sys
import numpy as np
import pandas as pd


'''
    Functions for Making decisions
'''
# Make decision for each line of test data with recursion
def make_decision(data, tree_result):
    decision = []
    
    # convert tree_result.values to list type
    value_list = list(tree_result.values())
    
    # To check index of matched element
    count_index = 0
    
    for i in tree_result.keys():
        tokens = i.split(':')
        attribute_name = tokens[0]
        attribute_value = tokens[1]

        # if data with same attribute name has contents
        if data[attribute_name] == attribute_value:
            # if type is class 'dict', child exists = recustion
            if str(type(value_list[count_index])) == "<class 'dict'>":
                result = make_decision(data, value_list[count_index])
                decision.append(result)
                break
            else:
                decision.append(value_list[count_index])
                
        count_index += 1   
    

    return decision

# Compare test data and tree to get decision result
def compare(attribute_name, test_data, tree_result, frequency):
    save_data = []
    decision = []
    
    save_data.append(attribute_name)
    for _, row in test_data.iterrows():
        # Save each values per line
        line = row.values

        result = make_decision(row, tree_result)

        # multiple list to single list
        single_list = convert_to_single(result, frequency)
        # Concatenate each line with decision result
        save_data.append(list(line) + single_list)
        
    return save_data


# Convert Multiple List to single list by recursion
def convert_to_single(data, frequency):
    if data[0]:
        if str(type(data[0])) == "<class 'str'>":
            return data
        else:
            result = sum(data, [])
            tmp = convert_to_single(result, frequency)
            return tmp
    elif not data[0]:
        tmp = []
        tmp.append(frequency)
        return tmp

'''
    Functions for training
'''
# function to stop recusion
def build_check(data):
    attribute_n = data.iloc[:,-1].unique()

    check = False
    if len(attribute_n) == 1:
        # answer is 1, so only one child will be made, no more choice
        check = False
    # 3 is most accurate
    elif len(data.columns) == 3:
        check = False
    else:
        check = True
    

    return check
    

# function to classify 
def classify(data_set, selected, max_ratio_column, majority_decision):
    save_unique = selected.unique()
    
    child_node = dict()
    
    for column in save_unique:
        # save row of data_set which match with column
        data_list = data_set.loc[selected == column]
        #child_node['node_name'] = max_ratio_column
        if build_check(data_list):
            # continue recursion
            tree_type = False
            child_node[max_ratio_column+":"+column] = create_tree(data_list.drop(max_ratio_column, 1), tree_type)       
        else:
            # stop recursion
            tree_type = True
            child_node[max_ratio_column+":"+column] = create_tree(data_list, tree_type)
    return child_node


# function for calculate entropy
def entropy(data):
    total = data.sum()

    total_entropy = 0
    for each in data:
        if each:
            total_entropy += each / total * math.log(each/total, 2)
        else:
            return 0
    return total_entropy


# function to calculate  gain ratio
def gain_ratio(data_table, total_row):
    total_gain = 0
    part_sum = 0
    
    # row is result of decision with unique column value
    # eg. if dt_train.txt, based column age, 
        # first column of age is <=30, and row will be [0 4]
        # 0 is frequency of NO, 4 is frequency of YES
    for row in data_table.values:
        rate = row.sum()/total_row
        total_gain += rate * entropy(row)
        part_sum += rate * math.log(rate,2)

    gain_ratio = total_gain / part_sum

    return gain_ratio


# function to build tree
def build(data_set, majority_decision):
    ratio = dict()
    total = len(data_set)

    # select last column which is attribute n
    decisions = data_set[data_set.columns[-1]]

    for column in data_set.columns[:-1]:
        values = data_set[column]

        frequency_table = pd.crosstab(values, decisions)

        # index will be column name, value will be calculated gain ratio
        #ratio[column] = gain_ratio(frequency_table, total_row)
        ratio[column] = gain_ratio(frequency_table, total)
    # get min of ratio 
    selected = min(ratio.keys(), key=(lambda k: ratio[k]))
    
    # Classify using selected columns using gain_ratio
    return classify(data_set, data_set[selected], selected, majority_decision)


# function to create tree
def create_tree(data_set, tree_type):
    # iloc[:,-1]: select last column, which contain decisions
    # value_counts(): find unique element and count frequency
    # idxmax(): select large one
    majority_decision = data_set.iloc[:,-1].value_counts().idxmax()

    if tree_type == False:
        return build(data_set,  majority_decision)
    else:
        return majority_decision


# function for decision tree
def decision_tree(training_data):
    tree_type = False

    tree = create_tree(training_data, tree_type)
    return tree

    
# read data
def load_file(file_name):
    dataset = []            # save data

    # open file
    read = open(file_name, 'r')

    # read lines
    for line in read:
        tokens = line.strip().split('\t')         # delete '\n' and split with '\t'
        dataset.append(tokens)

    # close opened file
    read.close()

    # convert to dataframe
    # set column as first row of training_data
    training_data = pd.DataFrame(dataset[1:], columns=dataset[0])

    return training_data


# write data
def write_file(file_name, data):
    # Open file
    w = open(file_name, 'w')

    # write each line to file
    for line in data:
        tmp =''
        count = 0
        for word in line:        
            tmp += str(word) + '\t'     
            count += 1
        # delete last indent by [:-1]
        tmp = tmp[:-1] +'\n'      

        w.write(tmp)
    
    w.close()

# main function 
if __name__ == "__main__":
    training_data = load_file(sys.argv[1])
    test_data = load_file(sys.argv[2])

    tree_result = decision_tree(training_data)
    
    
    frequency = training_data.iloc[:,-1].value_counts().idxmax()
 
    # Use tree_result to judge test_data
    saved_data = compare(list(training_data.columns), test_data, tree_result, frequency)
    
    
    # write to result file
    write_file(sys.argv[3], saved_data)
        
