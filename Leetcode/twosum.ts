function twoSum(nums: number[], target: number): number[] {
    
    let indeces: number[] = [0,0]
    
    for(let val in nums){
      let comp: number = target - nums[val]; 
        if(nums.indexOf(comp) != -1 && nums.indexOf(comp) != parseInt(val)){
            indeces = [nums.indexOf(comp),parseInt(val)]
        }
    }
    
    return indeces;
    
};

/*
Runtime: 232 ms, faster than 10.76% of TypeScript online submissions for Two Sum.
Memory Usage: 38.5 MB, less than 48.65% of TypeScript online submissions for Two Sum.

Aprox 1h20m
*/