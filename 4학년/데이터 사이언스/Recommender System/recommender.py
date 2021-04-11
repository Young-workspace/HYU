import numpy as np
import sys


'''     
* Class for recommeder system *

self.data: training data
self.max_user_id: User id that is maximum
self.max_item_id: Item id that is maximum
self.max_rating: maximum rating
self.min_rating: minimum rating
self.result : rating result, initialy -1
self.avg : average of rating
self.similarity: Similarity Matrix
'''
class Recommeder_system():
    def __init__(self, training_data: str):
        self.data = training_data        
        self.max_user_id = max(self.data[:, 0])
        self.max_item_id = max(self.data[:, 1])
        self.max_rating = max(self.data[:, 2])
        self.min_rating = min(self.data[:,2])
        
        # make 2D array with number of user and number of item 
        # initialize with -1
        self.result = np.full((self.max_user_id,self.max_item_id), -1)
       
        for row in self.data:
            user, item, rating, time_stamp = row
            self.result[user-1][item-1] = rating

        self.avg = self.get_avg()
        self.similarity = self.get_similarity()
       

    # Compute average rating for each items
    def get_avg(self):
        avg = np.zeros(self.max_user_id)
        for id in range(self.max_user_id):
            # Check it items in result[id] >=0 or not and save true, false
            rated = self.result[id] >= 0

            # Sum(rated items) / total_number_of_rated_items
            avg[id] = sum(self.result[id][rated])/len(rated[rated])
        return avg


    # Compute similarity 
    def get_similarity(self):
        similar_matrix = np.zeros([self.max_user_id, self.max_user_id])

        for i in range(len(self.result)):
            for j in range(i+1, len(self.result)):
                # similar means to call cosine function
                similar_matrix[j][i] = self.cosine(self.result[i], self.result[j])
                similar_matrix[i][j] = similar_matrix[j][i]

        return similar_matrix


    # Calculate Cosine Similarity
    def cosine(self, result_x, result_y):
        # item save boolean that satisfy >=0
        item = (result_x >= 0) * (result_y >= 0)
        
        if len(item[item]) == 0:
            return 0

        vec1 = result_x[item]
        vec2 = result_y[item]
        # return result of cosine similairy
        return vec1.dot(vec2)/(sum(vec1**2) + sum(vec2 **2))
    

    # Function for Aggregation of rating
    def aggregation(self, user, item):
        try:
            # save item's rate
            rate = self.result[:, item]

            # if rate >=0 save true to rated, else save false
            rated = rate >= 0
 
            neighbors = self.similarity[user, rated]
            user_rating = rate[rated] - self.avg[rated]

            # If no neighbor exists
            if sum(neighbors) == 0:
                return self.avg[user]

            sigma = sum(neighbors * user_rating) / sum(neighbors)
            rating = self.avg[user] + sigma

            # Change value smaller than min_rating to min_rating
            # Change value greater than max_rating to max_rating
            return np.clip(rating, self.min_rating, self.max_rating)


        # if index exceed limits
        # if item does not exist in training data
        except IndexError:      
            return self.avg[user]


# Function to Read File
def load_file(file_name):
    # open file
    with open(file_name, 'r') as f:
        # with loop using map and lambda
        return np.array(list(map(lambda s: s.strip().split(), f.readlines()))).astype(int)



# Main Function
if __name__ == '__main__':
    training_file = sys.argv[1]
    test_file = sys.argv[2]

    training_data = load_file(training_file)
    
    print('start training data')
    training_result = Recommeder_system(training_data)

    print('start prediction')

    # write result to file
    with open(training_file + '_prediction.txt', 'w') as w:
        # Save test data
        test_data = load_file(test_file)

        for i in range(len(test_data)):
            user, item, rating, time_stamp = test_data[i]
            
            # Use aggregation to predict rating
            result = training_result.aggregation(user-1, item-1)
            w.write('%d\t%d\t%f\n' % (user, item, result))
    
    print('complete')