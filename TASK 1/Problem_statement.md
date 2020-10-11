Given a string (consisting of lowercase english alphabets). Find number of prefixes which are also suffixes.

Prefix : String formed by deleting one or more characters from the end
Suffix : String formed by deleting one or more characters from start

Eg : abbcabb
	
	Prefixes : a, ab, abb, abbc, abbca, abbab
	Suffixes : b, bb, abb, cabb, bcabb, bbcabb
	
	Here abb is both prefix and suffix, so answer is 1

Solution of this problem is given in "solution.cpp" file present in Task-1 folder. But there are some bugs in it. You have to identify those bugs and make a PR with the corrected solution.

1. You can't change the logic or structure of the solution.
2. If you are changing any of the constants defined(like mod or p), the absolute change should be <=10
 	i.e. |new_value - old_value| <= 10
3. Expected complexity of solution : O(length of string * log(mod))
4. Your solution will be judged on Testcases made by us before merging.
5. Put proper comments and the logic behind that for every changes you make.

NOTE : The corrected code for each task should be submitted in the submission folder for each Task in format. [IIT20xxxx.cpp]
