
#include <string>
#include <map>
#include <algorithm>
#include <stack>
#include "leetcode_function.h"

using namespace std;

int IsPalindrome(const string input_s)
{

	const int s_length = input_s.length();


	int delete_index = -1;
	int check_i_s = -1;
	int check_i_e = s_length;
	bool is_symmetry = true;
	while (check_i_s <= check_i_e)
	{
		check_i_s = check_i_s + 1;
		check_i_e = check_i_e - 1;

		if (input_s[check_i_s] != input_s[check_i_e])
		{
			if (delete_index == -1 && input_s[check_i_s + 1] == input_s[check_i_e])
			{
				delete_index = check_i_s;
				check_i_s = check_i_s + 1;
			}
			else if (delete_index == -1 && input_s[check_i_s] == input_s[check_i_e - 1])
			{
				delete_index = check_i_e;
				check_i_e = check_i_e - 1;
			}
			else
			{
				is_symmetry = false;
				break;
			}
		}

	}


	int ans = is_symmetry ? delete_index : -2;

	return ans;
}


vector<int> twoSum(vector<int>& nums, int target)
{
	vector<int> ans;

	
	{
		map <int, int> hashMap;
		for (int i = 0; i < nums.size(); ++i)
		{
			const map <int, int>::iterator iter = hashMap.find(target - nums[i]);
			if (iter != hashMap.end())
			{
				ans.push_back(iter->second);
				ans.push_back(i);
			}
			else
			{
				hashMap.insert(pair<int, int>(nums[i], i));
			}

		}
	}
	return ans;
}


ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode l3h;

	ListNode* l1ing = l1;
	ListNode* l2ing = l2;
	ListNode* l3_last = &l3h;

	int is_carry = 0;
	while (l1ing || l2ing || is_carry)
	{
		const int sum = is_carry + (l1ing ? l1ing->val : 0) + (l2ing ? l2ing->val : 0);
		is_carry = sum / 10;
		l3_last->next = new ListNode(sum % 10);

		l1ing = l1ing ? l1ing->next : nullptr;
		l2ing = l2ing ? l2ing->next : nullptr;
		l3_last = l3_last->next;
	}
	
	return l3h.next;
}



int lengthOfLongestSubstring(string s)
{
	int max_len = 0;
	int last_begin_index = -1;
	vector<int> last_indexs(256, -1);
	for (int i=0;i<s.length();++i)
	{
		const int temp_last_index = last_indexs[s[i]];
		last_begin_index = max(last_begin_index, temp_last_index);
		max_len = max(max_len, i - last_begin_index);
		last_indexs[s[i]] = i;
	}
	return max_len;
}



double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
	const int total_size = nums1.size() + nums2.size();
	vector<int> mid_index;
	
	if (total_size % 2)
	{
		mid_index.push_back(total_size / 2);
	}
	else
	{
		mid_index.push_back(total_size / 2 - 1);
		mid_index.push_back(total_size / 2);
	}


	int sum = 0;
	int mid_num = 0;
	int i1 = 0;
	int i2 = 0;
	while (mid_index.size())
	{
		int temp_value = 0;
		if (i2 >= nums2.size()  || ( i1 < nums1.size() && nums1[i1] <= nums2[i2]))
		{
			temp_value = nums1[i1];
			i1 = i1 + 1;
		}
		else
		{
			temp_value = nums2[i2];
			i2 = i2 + 1;
		}
		if (i1 + i2 - 1 >= mid_index[0])
		{
			mid_index.erase(mid_index.begin());
			++mid_num;
			sum = sum + temp_value;
		}
	}
	
	return (double)sum / mid_num;


}


pair<int, int> findPalindromeFromCenter(const string& s, int left, int right)
{
	while (left >= 0 && right< s.length() && s[left]==s[right])
	{
		--left; ++right;
	}
	return pair<int, int>(left+1, right-1);
}

string longestPalindrome(string s)
{
	int center = 0;
	int max_len_b = 0;
	int max_len_e = 0;

	if (s.length()>0)
	{
		for (int i=0;i<s.length();++i)
		{
			const pair<int, int> se1= findPalindromeFromCenter(s, i, i);
			if (max_len_e - max_len_b < se1.second-se1.first)
			{
				max_len_b = se1.first;
				max_len_e = se1.second;
			}
			const pair<int, int> se2 = findPalindromeFromCenter(s, i, i + 1);
			if (max_len_e - max_len_b < se2.second - se2.first)
			{
				max_len_b = se2.first;
				max_len_e = se2.second;
			}
		}
	}

	return s.substr(max_len_b, max_len_e - max_len_b+1);

}



string convert(string s, int numRows)
{
	string output_ans;

	const int cyc_num = numRows + numRows - 2;
	if (cyc_num)
	{
		string* rows_ans = new string[cyc_num];

		for (int old_i = 0; old_i < s.length(); ++old_i)
		{
			const int cyc_i = old_i % cyc_num;
			int row_i = min(cyc_i, cyc_num - cyc_i);
			rows_ans[row_i].push_back(s[old_i]);
		}

		for (int row_i = 0; row_i < numRows; ++row_i)
		{
			output_ans = output_ans + rows_ans[row_i];
		}
		delete[] rows_ans;

	}
	else
	{
		output_ans = s;
	}

	return output_ans;
}


int reverse(int x) 
{
	int reverse_x = 0;
	while (x)
	{
		const int remainder = x % 10;
		if (reverse_x > INT_MAX / 10 || (reverse_x == INT_MAX / 10 && remainder > 7))
		{
			return 0;
		}
		if (reverse_x < INT_MIN / 10 || (reverse_x == INT_MIN / 10 && remainder < -8))
		{
			return 0;
		}
		reverse_x = reverse_x * 10 + x % 10;
		x /= 10;
	}
	return reverse_x;
}



int myAtoi(string str) {

	int num_begin_i = 0;
	for (; num_begin_i <str.length();++num_begin_i)
	{
		if (str[num_begin_i]!=32)
		{
			break;
		}
	}

	bool is_negative = false;
	if (str[num_begin_i] == '-')
	{
		is_negative = true;
		++num_begin_i;
	}
	else if (str[num_begin_i] == '+')
	{
		++num_begin_i;
	}

	int num = 0;
	for (int i = num_begin_i; i < str.length(); ++i)
	{
		if (str[i] > 57 || str[i] < 48)
		{
			break;
		}
		if (num > INT_MAX / 10 || num == INT_MAX / 10 && str[i] > 7 + 48)
		{
			return INT_MAX;
		}
		if (num < INT_MIN / 10 || num == INT_MIN / 10 && str[i] > 8 + 48)
		{
			return INT_MIN;
		}
		num = num * 10 + (is_negative?-1:1)*(str[i] - 48);
	}

	return num;
}


bool isPalindrome(int x)
{
	if (x < 0)
	{
		return false;
	}

	return x == reverse(x);
}



int maxArea(vector<int>& height) {

	int max_area = 0;
	int i = 0;
	int j = height.size()-1;
	while (i<j)
	{
		max_area = max(max_area, min(height[i], height[j])* (j - i));
		height[i] < height[j] ? ++i : --j;
	}
	return max_area;
}


string intToRoman(int num) 
{
	
	string M[] = { "", "M", "MM", "MMM" };
	string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
	return M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10] + I[num % 10];

}


int romanToInt(string s) {
	string dict[] = { "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" };
	int num[] = { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };
	
	int total_num = 0;
	int s_i = 0;
	int d_i = 0;
	while(s_i<s.length())
	{
		if (dict[d_i] == s.substr(s_i, dict[d_i].size()))
		{
			s_i = s_i + dict[d_i].length();
			total_num = total_num + num[d_i];
		}
		else
		{
			++d_i;
		}

	}
	return total_num;

}




string longestCommonPrefix(vector<string>& strs) 
{
	if (strs.size())
	{

		int max_common_len = INT_MAX;
		for (int i=0;i<strs.size();++i)
		{
			max_common_len = min(max_common_len, (int)strs[i].length());
		}

		int i = 0;
		while(i<max_common_len)
		{
			char const * const p_c = &strs[0][i];
			for (int s_i=1;s_i<strs.size();++s_i)
			{
				if (*p_c != strs[s_i][i])
				{
					return strs[0].substr(0,i);
				}
			}
			++i;
		}
		return strs[0].substr(0, i);
	}

	return "";
}




vector<vector<int>> threeSum(vector<int>& nums) {

	std::sort(nums.begin(), nums.end());

	vector<vector<int>>ans;
	for (int i=0;i<nums.size();++i)
	{
		if (i==0||nums[i]!=nums[i-1])
		{
			int second_i = i + 1;
			int third_i = nums.size() - 1;
			while (second_i < third_i)
			{
				const int sum = nums[i] + nums[second_i] + nums[third_i];
				if (sum == 0)
				{
					if (!ans.size()||*(--ans.end()) != vector<int>{nums[i], nums[second_i], nums[third_i]})
					{
						ans.push_back(vector<int>{nums[i], nums[second_i], nums[third_i]});
					}
					--third_i;
				}
				else if (sum > 0)
				{
					--third_i;
				}
				else
				{
					++second_i;
				}
			}
		}
		
	}
	return ans;

#ifdef FALSE
	vector<int> sort_nums(nums);
	sort(sort_nums.begin(), sort_nums.end());
	
	vector<vector<int>>ans;
	for (int i=0;i< sort_nums.size(); ++i)
	{
		if (i > 0 && sort_nums[i] == sort_nums[i - 1])
		{
			continue;
		}
		for (int j = i+1; j < sort_nums.size(); ++j)
		{
			if (j > i + 1 && sort_nums[j] == sort_nums[j - 1])
			{
				continue;
			}
			for (int k = j+1; k < sort_nums.size(); ++k)
			{
				if (k>j+1&& sort_nums[k]== sort_nums[k-1])
				{
					continue;
				}
				if (sort_nums[i]+ sort_nums[j]+ sort_nums[k]>0)
				{
					break;
				}
				else if((sort_nums[i] + sort_nums[j] + sort_nums[k])==0)
				{
					ans.push_back(vector<int>{sort_nums[i], sort_nums[j], sort_nums[k]});
				}

			}
		}
	}

	return ans;
#endif
}



int threeSumClosest(vector<int>& nums, int target) {

	std::sort(nums.begin(), nums.end());

	int clostest_sum = nums[0]+nums[1]+nums[2];
	for (int i = 0; i < nums.size(); ++i)
	{
		if (i == 0 || nums[i] != nums[i - 1])
		{
			int second_i = i + 1;
			int third_i = nums.size() - 1;
			while (second_i < third_i)
			{
				const int sum = nums[i] + nums[second_i] + nums[third_i];

				if (abs(clostest_sum-target)>abs(sum-target))
				{
					clostest_sum = sum;
				}

				if (sum >= target)
				{
					--third_i;
				}
				else
				{
					++second_i;
				}
			}
		}

	}
	return clostest_sum;

}




void letterCombinationsDFS(vector<string>* const p_ss, string temp_s, const string& digits, int remaind_index) {
	const static string map[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

	if (remaind_index<digits.size())
	{
		for (int i=0;i< map[digits[remaind_index]-48].length();++i)
		{
			temp_s[remaind_index] = map[digits[remaind_index] - 48][i];
			letterCombinationsDFS(p_ss, temp_s, digits, remaind_index+1);
		}
	}
	else
	{
		p_ss->push_back(temp_s);
	}
}
vector<string> letterCombinations(string digits) {

	vector<string> ans;
	if (digits.size())
	{
		string temp_s = digits;
		letterCombinationsDFS(&ans, temp_s, digits, 0);
	}
	return ans;
}



vector<vector<int>> fourSum(vector<int>& nums, int target) {

	sort(nums.begin(), nums.end());
	
	vector<vector<int>> ans;
	map<int, pair<int, int>> hashMap;
	for (int i=0;i<nums.size();++i)
	{
		for (int j = i + 1; j < nums.size(); ++j)
		{
			const int key = nums[i] + nums[j];
			const map<int, pair<int, int>>::iterator iter = hashMap.find(target - key);
			if (iter != hashMap.end())
			{
				vector<int> a_ans{ iter->second.first, iter->second.second, nums[i], nums[j]};
				sort(a_ans.begin(), a_ans.end());
				if (ans.end() == find(ans.begin(), ans.end(), a_ans))
				{
					ans.push_back(a_ans);
				}
			}
			hashMap.insert(pair<int, pair<int, int>>{key, {nums[i], nums[j]}});
		}
	}
	return ans;
}






ListNode* removeNthFromEnd(ListNode* head, int n) {

	ListNode** node_address_array = new ListNode*[n + 1];
	
	int last_index = 0;

	ListNode* this_node = head;
	while (this_node)
	{
		++last_index;
		if (last_index >= n + 1)
		{
			last_index = 0;
		}
		node_address_array[last_index] = this_node;
		this_node = this_node->next;
	}
	
	const int delete_node_index = (last_index + 2) % (n + 1);
	const int before_delete_index = (last_index + 1) % (n + 1);
	
	ListNode* new_head = nullptr;
	if (node_address_array[delete_node_index] == head)
	{
		new_head = node_address_array[delete_node_index]->next;
	}
	else
	{
		new_head = head;
		node_address_array[before_delete_index]->next = node_address_array[delete_node_index]->next;
	}
	delete node_address_array[delete_node_index];
	return new_head;
}



bool isValid(string s) 
{

	stack<char> parentheses;
	
	for (int i=0;i<s.length();++i)
	{
		switch (s[i])
		{
		default:
			break;
		case '(':
			parentheses.push('(');
			break;
		case '{':
			parentheses.push('{');
			break; 
		case '[':
			parentheses.push('[');
			break;
		case ']':
			if (parentheses.size() && '[' == parentheses.top())
			{
				parentheses.pop();
			}
			else
			{
				return false;
			}
			break;
		case ')':
			if (parentheses.size() && '(' == parentheses.top())
			{
				parentheses.pop();
			}
			else
			{
				return false;
			}
			break;
		case '}':
			if (parentheses.size() && '{' == parentheses.top())
			{
				parentheses.pop();
			}
			else
			{
				return false;
			}
			break;
		}

	}

	return !parentheses.size();

}



ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
	ListNode list_head;

	ListNode* p_merging_list = &list_head;
	while (l1&&l2)
	{
		if (l1->val< l2->val)
		{
			p_merging_list->next = l1;
			l1 = l1->next;
		}
		else
		{
			p_merging_list->next = l2;
			l2 = l2->next;
		}
		p_merging_list = p_merging_list->next;
	}
	
	if (l1)
	{
		p_merging_list->next = l1;
	}
	else
	{
		p_merging_list->next = l2;
	}
	return list_head.next;
};




void generateParenthesisDSF(const int n, string a_s, vector<string>& s)
{
	int l_n = 0;
	for (int i=0;i<a_s.length();++i)
	{
		if (a_s[i]=='(')
		{
			++l_n;
		}
	}

	int r_n = 0;
	for (int i = 0; i < a_s.length(); ++i)
	{
		if (a_s[i] == ')')
		{
			++r_n;
		}
	}
	if (a_s.length()==n*2)
	{
		s.push_back(a_s);
		return;
	}
	if (l_n<n)
	{
		generateParenthesisDSF(n, a_s + '(', s);
	}
	if (r_n<l_n)
	{
		generateParenthesisDSF(n, a_s + ')', s);
	}

}
vector<string> generateParenthesis(int n)
{
	vector<string> s;
	generateParenthesisDSF(n, "(", s);
	return s;
}



ListNode* mergeKLists(vector<ListNode*>& lists)
{
	if (lists.size() == 0)
	{
		return nullptr;
	}
	else if (lists.size()==1)
	{
		return lists[0];
	}
	else if (lists.size() == 2)
	{
		return mergeTwoLists(lists[0], lists[1]);
	}
	else
	{
		const int mid_i = lists.size()/2;
		vector<ListNode*> list1(lists.begin(), lists.begin() + mid_i + 1);
		vector<ListNode*> list2(lists.begin() + mid_i + 1, lists.end());
		return mergeTwoLists(mergeKLists(list1), mergeKLists(list2));
	}


#ifdef FALSE
	ListNode list_header(0);
	
	ListNode* p_merging = &list_header;
	while (1)
	{
		int small_i = -1;
		for (int i = 0; i < lists.size(); ++i)
		{
			if (lists[i] && (small_i == -1 || lists[i]->val < lists[small_i]->val))
			{
				small_i = i;
			}

		}
		if (small_i>=0)
		{
			p_merging->next = lists[small_i];
			p_merging = p_merging->next;
			lists[small_i] = lists[small_i]->next;
		}
		else
		{
			break;
		}

	}

	return list_header.next;
#endif
}


ListNode* swapPairs(ListNode* head) 
{
	ListNode list_head;
	list_head.next = head;
	
	ListNode* p_ing = &list_head;
	while (p_ing)
	{
		if (p_ing->next&&p_ing->next->next)
		{
			ListNode* p_temp1 = p_ing->next;
			ListNode* p_temp2 = p_ing->next->next;
			ListNode* p_temp3 = p_ing->next->next->next;
			p_ing->next = p_temp2;
			p_ing->next->next = p_temp1;
			p_ing->next->next->next = p_temp3;
			p_ing = p_ing->next->next;
		}
		else
		{
			break;
		}
	}
	return list_head.next;
}


ListNode* ReverseList(ListNode* const head, const int k)
{
	ListNode* p_ing = head;

	if (p_ing)
	{
		for (int i = 0; i < k-1; ++i)
		{
			if (p_ing->next)
			{
				p_ing = p_ing->next;
			}
			else
			{
				return head;
			}
		}

		ListNode* const p_last = p_ing->next;
		p_ing = head;
		ListNode* p_old = head->next;
		
		while (p_old && p_old!=p_last)
		{
			ListNode* const p_temp = p_old;
			p_old = p_old->next;
			p_temp->next = p_ing;
			p_ing = p_temp;
		}
		head->next = p_last;
	}

	return p_ing;
}

ListNode* reverseKGroup(ListNode* head, int k) 
{
	ListNode list_head;
	list_head.next = head;

	ListNode* p_ing = &list_head;
	while (p_ing)
	{
		ListNode*const p_next = p_ing->next;
		p_ing->next = ReverseList(p_ing->next, k);
		p_ing = p_next;
	}
	return list_head.next;
}




int removeDuplicates(vector<int>& nums)
{
	if (nums.size())
	{
		int new_i = 0;
		for (int old_i = 1; old_i < nums.size(); ++old_i)
		{
			if (nums[new_i] != nums[old_i])
			{
				nums[++new_i] = nums[old_i];
			}
		}
		return new_i + 1;
	}
	return 0;

}


int removeElement(vector<int>& nums, int val) 
{
	if (nums.size())
	{
		return remove(nums.begin(), nums.end(), val) - nums.begin();
	}
	return 0;




	int i = 0;
	int j = nums.size() - 1;
	while(i<=j)
	{
		if (nums[i]==val)
		{
			swap(nums[i], nums[j]);
			--j;
		}
		else
		{
			++i;
		}
	}
	return i;
}



int strStr(string haystack, string needle)
{
	if (needle.empty()) return 0;

	int* kmp_value = new int[needle.size()];
	
	for (int i = needle.size()-1;i>=0;--i)
	{
		kmp_value[i] = 0;
	}
	for (int i = needle.size() - 1; i > 0; --i)
	{
		if (i< needle.size() - 1 && kmp_value[i+1]>0)
		{
			kmp_value[i] = kmp_value[i + 1]-1;
		}
		else
		{
			for (int j = i-1; j > 0; --j)
			{
				const string sub_s1 = needle.substr(i - j, j);
				const string sub_s2 = needle.substr(0, j);
				if (sub_s1 == sub_s2)
				{
					kmp_value[i] = j;
					break;
				}
			}
		}
	}


	int match_index = -1;
	int check_i = 0;

	for (int scan_i=0;scan_i+needle.size()-check_i<=haystack.size();++scan_i)
	{
		if (haystack[scan_i] == needle[check_i])
		{
			if (++check_i>=needle.size())
			{
				match_index = scan_i - needle.size() + 1;
				break;
			}
		}
		else
		{
			if (check_i > 0)
			{
				--scan_i;
			}
			check_i = kmp_value[check_i];
		}

	}

	delete[] kmp_value; kmp_value = nullptr;



	return match_index;
}






int divide(int dividend, int divisor) 
{

}

