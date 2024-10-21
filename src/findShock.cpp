#include "findShock.h"



void findShock(std::map<int, std::set<std::string>> &signal_sets, std::map<int, std::set<std::string>> &gate_sets,
               std::map<int, std::set<std::string>>  &loop_other_signals, std::unordered_map<std::string, std::vector<std::string>>& gates,
               std::vector<int> &shock_location, const std::string &filename1, const std::string &filename2){
                   int cricle_flag = gate_sets.size();
                   int shock_count = 0;
                   int unshock_count = 0;
                   int allElements = 0;
                   int gateSize = 0;

                    std::cout << "find shock success" << std::endl;
                   for (int i = 0; i < cricle_flag; i++)
                   {
                       std::set<std::string>& gate_set = gate_sets[i+1];
                       //环外信号
                       std::set<std::string>& loop_other_signal = loop_other_signals[i+1];
                       std::set<std::string>& loop_signal = signal_sets[i+1];


                       allElements = loop_other_signal.size();
                       gateSize = gate_set.size();

                       int index = 0;
                       std::bitset<32> binary(0);
                       //std::vector<bool> result = decimalToPaddedBinary(decimalNumber, numBits);
                       std::map<std::string, int> other_loop_num;
                       std::map<std::string,bool> gate_num;


                       for (const auto elem : loop_other_signal)
                       {
                           other_loop_num[elem] = index;
                           index++;
                           if (index > allElements)
                           {
                               std::cout << "there is wrong in the loop_other_signal match index" << std::endl;
                           }
                       }

                       int shock = 0;
                       for (int decimalNumber = 0; decimalNumber < pow(2,allElements); decimalNumber++)
                       {
                           int flag = 0;
                           binary=decimalNumber;

                           bool case_0 = 0, case_1 = 1;
                           bool case_0_y = 0, case_1_y = 1;

                           for (int j = 0; j < gateSize; j++)
                           {   
                               auto it = gate_set.begin();
                               std::advance(it,j);
                               std::string current_gate_port = *it;
                               std::string current_gate = current_gate_port.substr(0,8);
                            
                               std::vector<std::string>& gate_info = gates[current_gate];
                               std::string& type_name = gate_info[0];
                               
                               std::string& current_type = type_name;
                               bool input;
                               if (type_name == "not1")
                               {
                                   input = 0;
                               }
                               else if (loop_other_signal.find(gate_info[2]) != loop_other_signal.end())
                               {
                                   input = binary[other_loop_num[gate_info[2]]];
                               }
                               else {
                                   input = binary[other_loop_num[gate_info[3]]];
                               }
                                gate_num[current_gate] = input; 
                        
                               case_0 = gateOutput(current_type,case_0, shock,input);
                               case_1 = gateOutput(current_type,case_1, shock,input);
                                   
                           }

                           if (case_0 != case_1) {
                               if (case_0 != case_0_y) {
                                   shock = 1;
                                   break;
                               }
                           }
                       }

                       if (shock) shock_count++;
                       else unshock_count++;

                       shock_location.emplace_back(shock);


                       std::string filename;
                       if (shock) filename = filename2;
                       else filename = filename1;
                       std::ofstream outFile(filename, std::ios::app);

                       if (shock) {outFile << shock_count << ")\n";}
                           else {outFile << unshock_count << ")\n";}

                       if (!loop_signal.empty()) {
                           outFile << "  Loop Signals: ";
                           auto it = loop_signal.begin();
                           outFile << *it;
                           

                           ++it;
                           for (; it != loop_signal.end(); ++it) {
                               outFile << ", " << *it;
                           }
                           outFile << std::endl;
                       }


                       if (!gate_set.empty()) {
                           outFile << "  Loop Gates: ";
                           auto it = gate_set.begin();
                           outFile << *it;

                           ++it;
                           for (; it != gate_set.end(); ++it) {
                               outFile << ", " << *it ;
                           }
                           outFile << std::endl;
                       }


                       if(shock){
                            if (!gate_set.empty()) {
                                outFile << "  Loop Gates: ";
                                auto it = gate_set.begin();
                                if (it->substr(13,14) == "1")
                                {
                                        outFile << it->substr(0,13) << "2";
                                }
                                else{
                                        outFile << it->substr(0,13) << "1";
                                }
                                outFile << "=" << gate_num[it->substr(0,8)] << ", ";

                                ++it;
                                for (; it != gate_set.end(); ++it) {
                                        //std::cout << "binary is:" << it->substr(0,8) << std::endl;
                                        if (it->substr(13,14) == "1")
                                        {
                                            outFile << it->substr(0,13) << "2";
                                        }
                                        else{
                                            outFile << it->substr(0,13) << "1";
                                        }
                                    outFile  <<  "=" << gate_num[it->substr(0,8)] << ", ";

                                }
                                outFile << std::endl;
                            }
                       }
                       outFile.close();
                       shock = 0;
                   }
               
               }


               // 函数将十进制数转换为二进制，并填充到指定的位数
std::vector<char> decimalToPaddedBinary(int decimalNumber, int numBits)
{
    // 创建一个 std::bitset 对象来存储指定长度的二进制数
    std::bitset<32> bs(decimalNumber);      // 32 是一个足够大的位数
    std::string binaryStr = bs.to_string(); // 获取二进制字符串

    // 提取最后 numBits 位的二进制字符串
    std::string paddedBinaryStr = binaryStr.substr(32 - numBits, numBits);

    // 将每一位字符分离到 vector 中
    std::vector<char> bitsList(paddedBinaryStr.begin(), paddedBinaryStr.end());

    return bitsList;
}





int gateOutput(std::string& current_gatetype, bool case_condition, int shock, bool current_input) {

    if (shock == 0)
    {
        if (current_gatetype == "or2"){
            case_condition = (case_condition || current_input);
            //std::cout << "gate type or;" << std::endl;
        }
        else if (current_gatetype == "not1"){
            case_condition = !case_condition;
            //std::cout << "gate type not;" << std::endl;
        }
        else if (current_gatetype == "and2"){
            case_condition = (case_condition && current_input);
            //std::cout << "gate type and;" << std::endl;
        }
        else if (current_gatetype == "nand2"){
            case_condition = !(case_condition && current_input);
            //std::cout << "gate type nand;" << std::endl;
        }
        else
            std::cout << "can't get correct type;" << std::endl;
    }
    else
        case_condition = !case_condition;

    return case_condition;
}
