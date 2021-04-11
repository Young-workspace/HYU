import numpy as numpy
import math
import sys
import time

classified_cluster = []       # index is id, value is location of cluster
num_of_cluster = 0
eps = 0
minPts = 0

# read data
def load_file(file_name):
    data = []

    # open file
    read = open(file_name, 'r')

    # read by lines
    for line in read:
        tokens = line.strip().split('\t')
        data.append(tokens)

    read.close()
    return data


# function to check whether object is neighbor or not
def is_neighbor(coor1, coor2):

    # x, y coordinate for first object
    x1 = float(coor1[0])
    y1 = float(coor1[1])
  
    # x, y coordinate for secoond object
    x2 = float(coor2[0])
    y2 = float(coor2[1])

    # use distance formula to calculate distance
    dist = math.sqrt((x1-x2) ** 2 + (y1-y2) ** 2)

    if dist <= eps:
        return True
    else:
        return False


# function to search neightboring data object
def search_neighbor(dataset, id):
    global eps

    neighbor = []

    # save ID's x coordinate and y coordinate
    first_coordinate = dataset[id][1:]

    for near in range(len(dataset)):
        second_coordinate = dataset[near][1:]
        if is_neighbor(first_coordinate, second_coordinate):
            neighbor.append(near)

    return neighbor


# function to clssfy clusters
def make_cluster(dataset, id, cluster):
    global  classified_cluster, num_of_cluster, eps, minPts
    
 
    # find neightboring data object
    neighbor_objects = search_neighbor(dataset, id)

    # if core point, Make cluster
    if len(neighbor_objects) >= minPts:
        classified_cluster[id] = cluster

        # make same cluster label to neighbors
        for n_id in neighbor_objects:
            classified_cluster[n_id] = cluster

        # loop until no more core point
        while len(neighbor_objects) > 0:
            n_id = neighbor_objects[0]

            # Use Recursion to expand cluster
            next_list = search_neighbor(dataset, n_id)

            # if core point, 
            if len(next_list) >= minPts:
                for num in range(len(next_list)):
                    index = next_list[num]

                    '''
                    if neighbor is not visited or is outlier
                    -> if -1: not visited
                    -> if -2: outlier
                    '''
                    if classified_cluster[index] == -1 or classified_cluster == -2:
                    #if classified_cluster[index] == -1:
                        # add to neighbor
                        neighbor_objects.append(index)
                        classified_cluster[index] = cluster
            
            # move to next neighboring object
            neighbor_objects = neighbor_objects[1:]
        return True

    else:
        classified_cluster[id] = -2             # -2 means outlier
        return False
    
        

# dbscan function, which start dbscan 
def db_scan(dataset):
    global  classified_cluster, num_of_cluster, eps, minPts

    classified_cluster = [-1] * len(dataset)         
    cluster = 0                         # cluster start from 0
    
    for id in range(len(dataset)):        # use range to get id
        if classified_cluster[id] == -1:
            if make_cluster(dataset, id, cluster):
                print('Finished Clustering \t ', cluster)
                print('=========================================')
                cluster += 1


# write result data
def write_file(input_name):
    global classified_cluster, num_of_cluster

    output_file = input_name.replace('.txt', '') + '_cluster_'

    for group in range(len(set(classified_cluster))-1):
        # if number of cluster > given cluster number, exit loop
        # if group >= num_of_cluster:
        #     break

        file_name = output_file + str(group) + '.txt'

        # Get index number based on group classified
        list_of_id = [i for i, j in enumerate(classified_cluster) 
                    if j == group]
        tmp = ''
        for id in list_of_id:
            tmp += str(id) + '\n'
        
        # open file
        w = open(file_name, 'w')

        w.write(tmp)

        w.close()


# main function
if __name__ == "__main__":
    dataset = load_file(sys.argv[1])

    num_of_cluster = int(sys.argv[2])
    eps = int(sys.argv[3])
    minPts = int(sys.argv[4])

    start = time.time()
    db_scan(dataset)
    
    write_file(sys.argv[1])


    