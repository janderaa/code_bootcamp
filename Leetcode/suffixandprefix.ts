/*
I tried to complete this one using a filter,
but since i don't know how to deal with this problem
of input: (see prefix and suffix dizzy image)

Who was the sadic one that thought this would be great as
use case? Satan itself and Bill Gates & Knuckles!

Well my abilities from now don't allow me to think another solution other than maybe using
other language that isn't TS since TS is a precompiler and JS is not good for huge 
loads of processing in terms of speed... at least in my knowledge.


nearly 1h20m

*/


class WordFilter {
    
    private w: string[];

    constructor(words: string[]) {
     
        this.w = words;
           
    }

    f(prefix: string, suffix: string): number {
        let index: number = -1;
        
        let wf: string[]= this.w.filter(elem => {
            return (elem.startsWith(prefix) && elem.endsWith(suffix))
        })
        
        if(wf.length>0){
            let largest: string = wf[0];
            for(const i in wf){
                if(wf[i]>largest){ largest = wf[i]}
            }
            
            index = this.w.indexOf(largest)
        }
        
        return index;
    }
}

/**
 * Your WordFilter object will be instantiated and called as such:
 * var obj = new WordFilter(words)
 * var param_1 = obj.f(prefix,suffix)
 */