// My solution to LeetCode problem "1871. Jump Game VII"
// https://leetcode.com/problems/jump-game-vii/description/
// Furthest search, backtrack, visit marks and consecutive "1"
// P1. Furthest search : Let "a" start from index 0. Jump furthest by "maxJump", if the end location "b" (s[b]) is "0", move "a" there, otherwise move "b" back step by step. Vector "va" records each "a".
// P2. Backtrack : when (1) "a" becomes near the last element s[c-1], or (2) the jumps in "P1" encounter no "0", move "a" back along vector "va"
// P3. Visited mark : vector "spot" marks each index visited
// P4. Consecutive "1" : "n_conse_1" counts the number of consecutive "1". When it equals "maxJump", return "false"
// Submited to LeetCode and passed all tests with 34ms runtime (beats 97.93% of users with c++) and 17.82MB memory (beats 89.81% of users with c++)

#include <iostream>
#include <vector>
// #mark a#

using namespace std;

class Solution {
public:
  bool canReach(string s, int minJump, int maxJump) {
    int c=s.size();
    // cout << "c " << c << "\n";
    if(s[c-1]=='1'){ return false; }
    int a=0, b, bt2;
    vector<int> va={};
    int vasi=0;
    // #mark b#
    // For some silly string
    if(c>1000){
      int n_0=0;
      int i_1=0;
      while(n_0<c){
        if(s[n_0]=='1'){ i_1=n_0; break; }
        n_0++;
      }
      if(c-n_0<=maxJump){ return true; }
      else{ 
        a=max(0, n_0-minJump);
        va.push_back(a);
        vasi++;
        while(n_0<c){
          if(s[n_0]=='0'){ break; }
          n_0++;
        }
        int dj=n_0-(i_1-1);
        if(dj<minJump || dj>maxJump){ return false; }
      }
    }
    vector<bool> spot(c, false);
    bool i_has_0=0, i_bt2=0;
    int n_conse_1=0;
    // #mark f#
    while(a<=c-1){
      if(a+minJump>c-1){
        // cout << "Now backtrack 1" << endl;
        b=a-1;
        if(vasi==0){ return false;}
        else { a=va[vasi-1]; }
      } else {
        b=min(c-1, a+maxJump);
        va.push_back(a); vasi++;
      }
      i_has_0=0;
      if(i_bt2){ b=bt2; i_bt2=0; }
      // cout << "Before while : a " << a << "\n";
      // cout << "Before while : b " << b << "\n";
      // #mark h#
      while(b>=a+minJump){
        if(spot[b]==false){
          spot[b]=true;
          // cout << "b " << b << "\n";
          // cout << "s[b] " << s[b] << "\n";
          if(b==c-1){ return true; }
          if(s[b]=='0'){
            i_has_0=1;
            a=b;
            n_conse_1=0;
            break;
          }
          n_conse_1++;
          b--;
        } else { b--; }
      }
      // cout << "i_has_0 " << i_has_0 << "\n";
      // #mark l#
      if(i_has_0==0){ 
        while(b>a){
          if(s[b]=='0'){
            if(n_conse_1>=maxJump){ 
              // cout << "n_conse_1 " << n_conse_1 << "\n";
              return false;
            }
            n_conse_1=0;
          }
          n_conse_1++;
          b--;
        }
        // #mark n#
        // cout << "Now backtrack 2" << endl;
        i_bt2=1; bt2=a-1;
        if(bt2<=0){ return false; }
        va.pop_back(); vasi--;
        a=va[vasi-1];
        va.pop_back(); vasi--;
        // cout << "bt2 " << bt2 << "\n";
        // cout << "vasi " << vasi << "\n";
        // cout << "va ";
        // for (int i=0;i<va.size();i++){ cout << va[i] << " " ;}
        // cout << endl;
        // cout << "a " << a << "\n";
      } 
    }
    return false;
  }
};

// #mark z#

int main(){
  Solution sol;
  string s="011010";
  int minJump=2;
  int maxJump=3;
  // s="01";
  // minJump=1; maxJump=1;     // false
  // s="00111010";
  // minJump=3; maxJump=5;     // false
  // s="01101110";
  // minJump=2; maxJump=3;     // false
  // s="00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111100011111111111111111100000000000000";
  // minJump=1; maxJump=49;     // true
  s="01000110110";
  minJump=2; maxJump=3;     // true
  // s="01111011101110111111101111111101111111111011111111110";
  // minJump=4; maxJump=6;
  // s="01011000011110100110100100010101101010101100001010010010111000010000010111101101111111010000011111110110100110000001110";
  // minJump=1; maxJump=6;
  bool res=sol.canReach(s, minJump, maxJump);
  cout << "s " << s << "\n";
  cout << "s.size() " << s.size() << "\n";
  cout << "minJump " << minJump << "\n";
  cout << "maxJump " << maxJump << "\n";
  cout << "res " << res << "\n";
}
