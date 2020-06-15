#pragma once

#include <string>
#include <vector>

//判斷輸入字串在扣掉其中一個字元後，能否成為回文字串。回傳-2為不能，-1不需要扣除即為回文字，0以上代表刪掉第幾個字可以成為回文字。
int IsPalindrome(const std::string input_s);


//從數列中找出兩個數字，相加剛好等於target。回傳兩數的index
std::vector<int> twoSum(std::vector<int>& nums, int target);




struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//You are given two non - empty linked lists representing two non - negative integers.The digits are stored in reverse order and each of their nodes contain a single digit.Add the two numbers and return it as a linked list.
//You may assume the two numbers do not contain any leading zero, except the number 0 itself.
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);



//Given a string, find the length of the longest substring without repeating characters.
int lengthOfLongestSubstring(std::string s);



//There are two sorted arrays nums1 and nums2 of size m and n respectively.
//Find the median of the two sorted arrays.The overall run time complexity should be O(log(m + n)).
//You may assume nums1 and nums2 cannot be both empty.
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2);



std::string longestPalindrome(std::string s);

std::string convert(std::string s, int numRows);

int reverse(int x);

int myAtoi(std::string str);


int maxArea(std::vector<int>& height);



std::string intToRoman(int num);


int romanToInt(std::string s);



std::string longestCommonPrefix(std::vector<std::string>& strs);



std::vector<std::vector<int>> threeSum(std::vector<int>& nums);


std::vector<std::string> letterCombinations(std::string digits);

std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target);



bool isValid(std::string s);


std::vector<std::string> generateParenthesis(int n);


ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);


ListNode* swapPairs(ListNode* head);



ListNode* reverseKGroup(ListNode* head, int k);


int removeDuplicates(std::vector<int>& nums);

int removeElement(std::vector<int>& nums, int val);

int strStr(std::string haystack, std::string needle);

int divide(int dividend, int divisor);




