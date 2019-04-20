# Medial-Axis-Thinning

Image processing algorithm to find the skeleton of the object. The skeleton is used for lossless image decompression.
The object is iteratively reduced on all sides until there are no more pixels to change.

Sample Input:
                  1                   
                1 1 1                 
              1 1 1 1 1               
            1 1 1 1 1 1 1             
          1 1 1 1 1 1 1 1 1           
        1 1 1 1 1 1 1 1 1 1 1         
      1 1 1 1 1 1 1 1 1 1 1 1 1       
    1 1 1 1 1 1 1 1 1 1 1 1 1 1 1     
  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1   
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
                  1                   
                1 1 1                 
              1 1 1 1 1               
            1 1 1 1 1 1 1             
          1 1 1 1 1 1 1 1 1           
        1 1 1 1 1 1 1 1 1 1 1         
      1 1 1 1 1 1 1 1 1 1 1 1 1       
    1 1 1 1 1 1 1 1 1 1 1 1 1 1 1     
  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1   
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 

Sample Output:
                  1                   
                  1                   
                  1                   
                  1                   
                  1                   
                  1                   
                  1                   
          1 1 1   1   1 1 1           
    1 1 1         1         1 1 1     
1 1               1               1 1 
                  1                   
                  1                   
                  1                   
                  1                   
                  1                   
                  1                   
                1 1 1                 
          1 1 1       1 1 1           
    1 1 1                   1 1 1     
1 1                               1 1 
