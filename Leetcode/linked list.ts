/**
 * Definition for singly-linked list.
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function addTwoNumbers(l1: ListNode | null, l2: ListNode | null): ListNode | null {
    var listAns: any = null
    
    if(l1 && l2){
        var ltemp: any = null;
        var ArrAns: Array<number> = [];
        
        let a: number = 0;
        let l1F = true;
        let l2F = true;
        
        let sum: number = 0;
        let l1Val: number = 0
        let l2Val: number = 0;
        
        while(l1F || l2F){
            
            if(!l1F){
                l1Val = 0;
            }else{l1Val = l1.val;}
            
            if(!l2F){
                l2Val = 0;
            }else{l2Val = l2.val;}
            
            console.log(l1F);
            console.log(l2F);
            sum = l1Val + l2Val + a;
            
            if(sum>=10){
                sum = sum - 10;
                a = 1;
            }else{
                a = 0;
            }
            
            ArrAns.push(sum)
            
            
            if(l1.next){
                l1 = l1.next;
            }else{l1F = false}
            
            if(l2.next){
                l2 = l2.next;
            }else{l2F = false}
            
            if(!l1F && !l2F && a>0){
                ArrAns.push(a);
            }
            
        }
        
        
        console.log(ArrAns);
        
        ArrAns.reverse();
        for(let i in ArrAns){
            listAns = new ListNode(ArrAns[i],ltemp);
            ltemp = listAns;
        }
        
    }
    
   
    
    return listAns;
     
};


/*
Runtime: 292 ms, faster than 5.25% of TypeScript online submissions for Add Two Numbers.
Memory Usage: 47 MB, less than 5.24% of TypeScript online submissions for Add Two Numbers.

nearly 01h50m to complete.
*/