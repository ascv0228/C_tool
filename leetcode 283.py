class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        i = 0
        while (nums != []):
            x = get0Index(nums)
            if(x == -1):
                break
            nums = nums[:x]+nums[x+1:]
            i+=1
        return nums+[0]*i
            
            
            
            
def get0Index(nums):
    try: return nums.index(0)
    except: return -1
