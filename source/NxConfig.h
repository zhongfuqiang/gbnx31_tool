// NxConfig.h: interface for the CNxConfig class.
// 实现对地址、命令、应答等应用层数据进行预配置，将这些信息写入注册表
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NXCONFIG_H__1DD12D49_5364_4329_A836_16957971D23E__INCLUDED_)
#define AFX_NXCONFIG_H__1DD12D49_5364_4329_A836_16957971D23E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Registry.h"
//#include "NxRulerTypes.h"
#include "Qgdw3761api.h"
#include "Gbnx_31.h"

#define INDEX_AFN_00_CONF   0//AFN 00 确认否认     
#define INDEX_AFN_01_RSET   1 //AFN 01 复位命令
#define INDEX_AFN_02_LINK   2//AFN 02 链路接口检测     
//#define INDEX_AFN_03_RELY   3//AFN 03 中继站命令     
#define INDEX_AFN_04_SETP   3//AFN 04 设置参数     
#define INDEX_AFN_05_CTRL   4//AFN 05 控制命令     
#define INDEX_AFN_06_AUTH   5//AFN 06 身份认证及密钥协商     
#define INDEX_AFN_08_CASC   6 //AFN 08 请求被级联终端主动上报     
//#define INDEX_AFN_09_CFIG   7//AFN 09 请求集中器配置及信息    
#define INDEX_AFN_0A_GETP   7//AFN 0A 查询参数     
//#define INDEX_AFN_0B_ASKT   9//AFN 0B 请求任务数据    
#define INDEX_AFN_0C_ASKT   8//AFN 0C 请求1类数据    
#define INDEX_AFN_0D_ASKR   9//AFN 0D 请求2类数据    
#define INDEX_AFN_0E_ASKE   10//AFN 0E 请求3类数据     
#define INDEX_AFN_0F_FILE   11//AFN 0F 文件传输     
#define INDEX_AFN_10_DATA   12//AFN 10 数据转发    


#define STR_AFN_00_CONF   "AFN 00 确认否认"     // 确认否认
#define STR_AFN_01_RSET   "AFN 01 复位命令"     // 复位
#define STR_AFN_02_LINK   "AFN 02 链路检测"     // 接口检测
//#define STR_AFN_03_RELY   "AFN 03 中继站命令 "     // 中继站命令
#define STR_AFN_04_SETP   "AFN 04 设置参数"     // 设置参数
#define STR_AFN_05_CTRL   "AFN 05 控制命令"     // 控制命令
#define STR_AFN_06_AUTH   "AFN 06 身份认证及密钥协商"     // 身份认证
#define STR_AFN_08_CASC   "AFN 08 请求被级联终端主动上报"     // 请求被级联终端主动上报 
//#define STR_AFN_09_CFIG   "AFN 09 请求集中器配置及信息"     // 请求终端配置
#define STR_AFN_0A_GETP   "AFN 0A 查询参数"     // 查询参数
//#define STR_AFN_0B_ASKT   "AFN 0B 请求任务数据"     // 请求任务数据
#define STR_AFN_0C_ASKT   "AFN 0C 请求任务数据"     // 请求1类数据 实时数据
#define STR_AFN_0D_ASKR   "AFN 0D 请求实时数据"     // 请求2类数据 历史数据
#define STR_AFN_0E_ASKE   "AFN 0E 请求事件记录"     // 请求3类数据 事件数据
#define STR_AFN_0F_FILE   "AFN 0F 文件传输"     // 文件传输
#define STR_AFN_10_DATA   "AFN 10 数据转发"     // 数据转发

/*
#define STR_AFN_00_CONF    "确认否认(AFN=00H)"     // 确认否认
#define STR_AFN_01_RSET   "复位命令(AFN=01H)"     // 复位
#define STR_AFN_02_LINK   "链路接口检测(AFN=02H)"     // 接口检测
#define STR_AFN_03_RELY   "中继站命令(AFN=04H)"     // 中继站命令
#define STR_AFN_04_SETP    "设置参数(AFN=04H)"     // 设置参数
#define STR_AFN_05_CTRL    "控制命令(AFN=05H)"     // 控制命令
#define STR_AFN_06_AUTH    "身份认证及密钥协商(AFN=06H)"     // 身份认证
#define STR_AFN_08_CASC    0x08     // 请求被级联终端主动上报 
#define STR_AFN_09_CFIG    "请求集中器配置及信息(AFN=09H)"     // 请求终端配置
#define STR_AFN_0A_GETP    "查询参数(AFN=0AH)"     // 查询参数
#define STR_AFN_0B_ASKT   "请求任务数据(AFN=0BH)"     // 请求任务数据
#define STR_AFN_0C_ASK1     "请求1类数据(AFN=0CH)"     // 请求1类数据 实时数据
#define STR_AFN_0D_ASK2  "请求2类数据(AFN=0DH)"     // 请求2类数据 历史数据
#define STR_AFN_0E_ASK3   "请求3类数据(AFN=0EH)"     // 请求3类数据 事件数据
#define STR_AFN_0F_FILE    "文件传输(AFN=0FH)"     // 文件传输
#define STR_AFN_10_DATA    "数据转发(AFN=10H)"     // 数据转发


*/

// AFN_00
#define STR_AFN_00_F1  "F1   全部确认/否认"
#define STR_AFN_00_F2  "F2   按数据单元标识确认和否认"
//#define STR_AFN_00_F3  "F3   按数据单元标识确认和否认"

// AFN_01
#define STR_AFN_01_F1   "F1   硬件初始化"
#define STR_AFN_01_F2   "F2   数据区初始化"
#define STR_AFN_01_F3   "F3   参数及全体数据区初始化(即恢复至出厂配置)"
#define STR_AFN_01_F4   "F4   参数(除与系统主站通信有关的)及全体数据区初始化"
#define STR_AFN_01_F5   "F5   指定数据清零"

// AFN_02
#define STR_AFN_02_F1   "F1   登录"
#define STR_AFN_02_F2   "F2   退出"
#define STR_AFN_02_F3   "F3   心跳"
#define STR_AFN_02_F4   "F4   确认（登录、退出、心跳）"

// AFN_03
#define STR_AFN_03_F1   "F1   中继站工作状态控制"
#define STR_AFN_03_F2   "F2   中继站工作状态查询"
#define STR_AFN_03_F3   "F3   中继站工作状态切换记录查义"
#define STR_AFN_03_F4   "F4   中继站运行状态统计查询"

// AFN 04
#define STR_AFN_04_F1   "F1   信息集中与交互终端上行通信口通信参数"
#define STR_AFN_04_F2   "F2   主(子)站参数"
#define STR_AFN_04_F3   "F3   信息集中与交互终端上行通信消息认证参数"
#define STR_AFN_04_F4   "F4   信息集中与交互终端组地址"
#define STR_AFN_04_F5   "F5   信息集中与交互终端IP地址和端口"
#define STR_AFN_04_F6   "F6   信息集中与交互终端级联通信参数"
#define STR_AFN_04_F7   "F7   信息集中与交互终端下行以太网端口通信参数"
// #define STR_AFN_04_F8   "F8   集中器上行通信工作方式(以太专网或虚拟专网)"

#define STR_AFN_04_F9   "F9   事件记录配置"
#define STR_AFN_04_F10  "F10  设备状态量输入参数"
// #define STR_AFN_04_F11  "F11  终端脉冲配置参数"
// #define STR_AFN_04_F12  "F12  终端/集中器状态量输入参数"
// #define STR_AFN_04_F13  "F13  终端电压/电流模拟量配置参数"
// #define STR_AFN_04_F14  "F14  终端总加组配置参数"
// #define STR_AFN_04_F15  "F15  有功总电能量差动超限事件参数设置"
// #define STR_AFN_04_F16  "F16  虚拟专网用户名、密码"

#define STR_AFN_04_F17  "F17  监测终端上行通信参数配置"
// #define STR_AFN_04_F18  "F18  终端功控时段"
// #define STR_AFN_04_F19  "F19  终端时段功控定值浮动系数"
// #define STR_AFN_04_F20  "F20  终端月电能量控定值浮动系数"
// #define STR_AFN_04_F21  "F21  终端电能量费率时段和费率数"
// #define STR_AFN_04_F22  "F22  终端电能量费率"
// #define STR_AFN_04_F23  "F23  终端催告警参数"

#define STR_AFN_04_F25  "F25  电气测量点配置参数"
#define STR_AFN_04_F26  "F26  电气测量点基本参数"
#define STR_AFN_04_F27  "F27  电气测量点电能量限值参数"
#define STR_AFN_04_F28  "F28  电气测量点功率因素越限值参数"
#define STR_AFN_04_F29  "F29  电气测量点谐波畸变率越限定值"
#define STR_AFN_04_F30  "F30  电气测量点闪变越限参数"
// #define STR_AFN_04_F31  "F31  载波从节点附属节点地址"


#define STR_AFN_04_F33  "F33  非电气测量点配置参数"
#define STR_AFN_04_F34  "F34  非电气测量点数据参数"
#define STR_AFN_04_F35  "F35  非电气测量点越限数据参数"
// #define STR_AFN_04_F36  "F36  终端上行通信流量门限设置"
// #define STR_AFN_04_F37  "F37  终端级联通信参数"
// #define STR_AFN_04_F38  "F38  1类数据配置设置"
// #define STR_AFN_04_F39  "F39  2类数据配置设置"

//6
// #define STR_AFN_04_F41  "F41  时段功控定值"
// #define STR_AFN_04_F42  "F42  厂休功控参数"
// #define STR_AFN_04_F43  "F43  功率控制的功率计算滑差时间"
// #define STR_AFN_04_F44  "F44  营业报停控参数"
// #define STR_AFN_04_F45  "F45  功控轮次设定"
// #define STR_AFN_04_F46  "F46  月电量控定值"
// #define STR_AFN_04_F47  "F47  购电量(费)控参数"
// #define STR_AFN_04_F48  "F48  电控轮次设定"

//7
#define STR_AFN_04_F49  "F49  冻结数据任务参数"

// 8
// #define STR_AFN_04_F57  "F57  终端声音告警允许/禁止设置"
// #define STR_AFN_04_F58  "F58  终端自动保电设置"
// #define STR_AFN_04_F59  "F59  电能表异常判别阈值设置"
// #define STR_AFN_04_F60  "F60  谐波限值"
// #define STR_AFN_04_F61  "F61  直流模拟量接入参数"
// 
// 9
// #define STR_AFN_04_F65  "F65  定时上报1类数据任务设置"
// #define STR_AFN_04_F66  "F66  定时上报2类数据任务设置"
// #define STR_AFN_04_F67  "F67  定时上报1类数据任务启动/停止设置"
// #define STR_AFN_04_F68  "F68  定时上报2类数据任务启动/停止设置"
// 10
// #define STR_AFN_04_F73  "F73  电容器参数"
// #define STR_AFN_04_F74  "F74  电容器投切运行参数"
// #define STR_AFN_04_F75  "F75  电容器保护参数"
// #define STR_AFN_04_F76  "F76  电容器投切控制方式"
// 
// 11
// #define STR_AFN_04_F81  "F81  直流模拟量变比"
// #define STR_AFN_04_F82  "F82  直流模拟量限值"
// #define STR_AFN_04_F83  "F83  直流模拟量冻结参数"

// AFN 05
//1
#define STR_AFN_05_F1    "F1   校时命令"
#define STR_AFN_05_F2    "F2   临时冻结命令"
#define STR_AFN_05_F3    "F3   允许信息集中与交互终端主动上报"
#define STR_AFN_05_F4    "F4   禁止信息集中与交互终端主动上报"
#define STR_AFN_05_F5    "F5   激活信息集中与交互终端连接主(子)站"
#define STR_AFN_05_F6    "F6   命令信息集中与交互终端断开连接"
// 2
#define STR_AFN_05_F9    "F9   遥控跳闸"
#define STR_AFN_05_F10   "F10  允许合闸"
// #define STR_AFN_05_F11   "F11  营业报停功控投入"
// #define STR_AFN_05_F12   "F12  当前功率下浮控投入"
// #define STR_AFN_05_F15   "F15  月电控投入"
// #define STR_AFN_05_F16   "F16  购电控投入"

//3
#define STR_AFN_05_F17   "F17  能效模型有效"
#define STR_AFN_05_F18   "F18  能效模型清除"
#define STR_AFN_05_F19   "F19  需求响应信息有效"
#define STR_AFN_05_F20   "F20  需求响应信息清除"
// #define STR_AFN_05_F23   "F23  月电控解除"
// #define STR_AFN_05_F24   "F24  购电控解除"

//4
#define STR_AFN_05_F25   "F25  启动定时上报冻结数据任务"
#define STR_AFN_05_F26   "F26  禁止定时上报冻结数据任务"
#define STR_AFN_05_F27   "F27  冻结数据任务启动"
#define STR_AFN_05_F28   "F28  冻结数据任务停止"
// #define STR_AFN_05_F29   "F29  允许终端主动上报"
// 
// #define STR_AFN_05_F31   "F31  对时命令"
// #define STR_AFN_05_F32   "F32  中文信息"
// 
// //5
// #define STR_AFN_05_F33  "F33  终端电保解除"
// #define STR_AFN_05_F34  "F34  催费告警解除"
// #define STR_AFN_05_F35  "F35  禁止终端与主站通话"
// #define STR_AFN_05_F36  "F36  终端剔除解除"
// #define STR_AFN_05_F37  "F37  禁止终端主动上报"
// #define STR_AFN_05_F38  "F38  激活终端连接主站"
// #define STR_AFN_05_F39  "F39  命令终端断开连接"
// 
// //6
// #define STR_AFN_05_F41  "F41  电容器控制投入"
// #define STR_AFN_05_F42  "F42  电容器控制解除"
// 
// //7
// #define STR_AFN_05_F49  "F49  命令指定通信端口暂停抄表"
// #define STR_AFN_05_F50  "F50  命令指定通信端口恢复抄表"
// #define STR_AFN_05_F51  "F51  命令指定通信端口重新抄表"
// #define STR_AFN_05_F52  "F52  初始化指定通信端口下的全部中继路由信息"
// #define STR_AFN_05_F53  "F53  删除指定通信端口下的全部电表"




// afn 06
#define STR_AFN_06_F1   "F1  身份认证请求"
#define STR_AFN_06_F2   "F2  身份认证响应"
#define STR_AFN_06_F3   "F3  取随机数请求"
#define STR_AFN_06_F4   "F4  取随机数响应"

// afn 8
#define STR_AFN_08_F1   "F1  请求被级联终端主动上报"

// afn 09
//1
// #define STR_AFN_09_F1   "F1  终端版本信息"
// #define STR_AFN_09_F2   "F2  终端支持的输入、输出及通信端口配置"
// #define STR_AFN_09_F3   "F3  终端支持的其他配置"
// 
// #define STR_AFN_09_F4   "F4  终端支持的参数配置"
// #define STR_AFN_09_F5   "F5  终端支持的控制配置"
// #define STR_AFN_09_F6   "F6  终端支持的1类数据配置"
// #define STR_AFN_09_F7   "F7  终端支持的2类数据配置"
// #define STR_AFN_09_F8   "F8  终端支持的事件记录配置"


// AFN 0A  查询参数
//1 
#define STR_AFN_0A_F1   "F1   查询信息集中与交互终端上行通信口通信参数"
#define STR_AFN_0A_F2   "F2   查询主(子)站参数"
#define STR_AFN_0A_F3   "F3   查询信息集中与交互终端上行通信消息认证参数"
#define STR_AFN_0A_F4   "F4   查询信息集中与交互终端组地址"
#define STR_AFN_0A_F5   "F5   查询信息集中与交互终端IP地址和端口"
#define STR_AFN_0A_F6   "F6   查询信息集中与交互终端级联通信参数"
#define STR_AFN_0A_F7   "F7   信息集中与交互终端下行以太网端口通信参数"
// #define STR_AFN_0A_F8   "F8   集中器上行通信工作方式"
//2
#define STR_AFN_0A_F9   "F9   查询事件记录配置"
#define STR_AFN_0A_F10  "F10  查询设备状态量输入参数"
#define STR_AFN_0A_F11  "F11  设备逻辑地址"
#define STR_AFN_0A_F12  "F12  查询设备版本信息"
#define STR_AFN_0A_F13  "F13  已配置电气测量点信息"
#define STR_AFN_0A_F14  "F14  已配置非电气测量点信息"
#define STR_AFN_0A_F15  "F15  设备支持的事件记录"
/*#define STR_AFN_0A_F16  "F16  虚拟专网用户名、密码"*/

// 3
#define STR_AFN_0A_F17  "F17  查询监测终端的上行通信参数"
// #define STR_AFN_0A_F18  "F18  终端功控时段"
// #define STR_AFN_0A_F19  "F19  终端时段功控定值浮动系数"
// #define STR_AFN_0A_F20  "F20  终端月电能量控定值浮动系数"
// #define STR_AFN_0A_F21  "F21  终端电能量费率时段和费率数"
// #define STR_AFN_0A_F22  "F22  终端电能量费率"
// #define STR_AFN_0A_F23  "F23  终端催告警参数"


//4
#define STR_AFN_0A_F25  "F25  查询电气测量点配置参数"
#define STR_AFN_0A_F26  "F26  查询电气测量点基本参数"
#define STR_AFN_0A_F27  "F27  查询电气测量点电能量限值参数"
#define STR_AFN_0A_F28  "F28  查询电气测量点功率因数越限值参数"
#define STR_AFN_0A_F29  "F29  查询电气测量点谐波畸变率越限定值"
#define STR_AFN_0A_F30  "F30  查询电气测量点闪变越限参数"
// #define STR_AFN_0A_F31  "F31  载波从节点附属节点地址"

//5
#define STR_AFN_0A_F33  "F33  查询非电气测量点配置参数"
#define STR_AFN_0A_F34  "F34  查询非电气测量点数据参数"
#define STR_AFN_0A_F35  "F35  查询非电气测量点数据越限参数配置"
// #define STR_AFN_0A_F36  "F36  终端上行通信流量门限设置"
// #define STR_AFN_0A_F37  "F37  终端级联通信参数"
// #define STR_AFN_0A_F38  "F38  1类数据配置设置"
// #define STR_AFN_0A_F39  "F39  1类数据配置设置"

//6
// #define STR_AFN_0A_F41  "F41  时段功控定值"
// #define STR_AFN_0A_F42  "F42  厂休功控参数"
// #define STR_AFN_0A_F43  "F43  功率控制的功率计算滑差时间"
// #define STR_AFN_0A_F44  "F44  营业报停控参数"
// #define STR_AFN_0A_F45  "F45  功控轮次设定"
// #define STR_AFN_0A_F46  "F46  月电量控定值"
// #define STR_AFN_0A_F47  "F47  购电量(费)控参数"
// #define STR_AFN_0A_F48  "F48  电控轮次设定"

//7
#define STR_AFN_0A_F49  "F49  查询冻结数据任务参数"

//8
#define STR_AFN_0A_F57  "F57  查询已配置监测终端信息"
// #define STR_AFN_0A_F58  "F58  终端自动保电设置"
// #define STR_AFN_0A_F59  "F59  电能表异常判别阈值设置"
// #define STR_AFN_0A_F60  "F60  谐波限值"
// #define STR_AFN_0A_F61  "F61  直流模拟量接入参数"

// 9
// #define STR_AFN_0A_F65  "F65  定时上报1类数据任务设置"
// #define STR_AFN_0A_F66  "F66  定时上报2类数据任务设置"
// #define STR_AFN_0A_F67  "F67  定时上报1类数据任务启动/停止设置"
// #define STR_AFN_0A_F68  "F68  定时上报2类数据任务启动/停止设置"
// 10
// #define STR_AFN_0A_F73  "F73  电容器参数"
// #define STR_AFN_0A_F74  "F74  电容器投切运行参数"
// #define STR_AFN_0A_F75  "F75  电容器保护参数"
// #define STR_AFN_0A_F76  "F76  电容器投切控制方式"
// 
// 11
// #define STR_AFN_0A_F81  "F81  直流模拟量变比"
// #define STR_AFN_0A_F82  "F82  直流模拟量限值"
// #define STR_AFN_0A_F83  "F83  直流模拟量冻结参数"


// AFN 0B
#define STR_AFN_0B_F1   "F1   请求定时上报1类数据任务" 
#define STR_AFN_0B_F2   "F2   请求定时上报2类数据任务"


// AFN 0C
//1 
#define STR_AFN_0C_F1   "F1   请求临时冻结命令的冻结数据"
// #define STR_AFN_0C_F2   "F2   请求（定时上报）冻结数据任务"

// #define STR_AFN_0C_F4   "F4   终端上行通信状态"
// #define STR_AFN_0C_F5   "F5   终端控制设置状态"
// #define STR_AFN_0C_F6   "F6   终端当前控制状态"
// #define STR_AFN_0C_F7   "F7   终端事件计数器当前值"
// #define STR_AFN_0C_F8   "F8   终端事件标志状态"

//2
#define STR_AFN_0C_F9   "F9   请求（定时上报）冻结数据任务"
// #define STR_AFN_0C_F10  "F10  终端与主站当日、月通信流量"
// #define STR_AFN_0C_F11  "F10  终端集中抄表状态信息"
// 
// //3
// #define STR_AFN_0C_F17  "F17  当前总加有功功率"
// #define STR_AFN_0C_F18  "F18  当前总加无功功率"
// #define STR_AFN_0C_F19  "F19  当日总加有功电能量"
// #define STR_AFN_0C_F20  "F20  当日总加无功电能量"
// #define STR_AFN_0C_F21  "F21  当月总加有功电能量"
// #define STR_AFN_0C_F22  "F22  当月总加无功电能量"
// #define STR_AFN_0C_F23  "F23  终端当前剩余电量(费)"
// #define STR_AFN_0C_F24  "F24  当前功率下浮控控后总加有功功率冻结值"
// 
// //4
// #define STR_AFN_0C_F25  "F25  当前三相及总有/无功功率、功率因数, 三相电压、电流、零序电流、视在功率"
// #define STR_AFN_0C_F26  "F26  A、B、C三相断相统计数据及最近一次断相记录"
// #define STR_AFN_0C_F27  "F27  电能表日历时钟、编程次数及其最近一次操作时间"
// #define STR_AFN_0C_F28  "F28  电表运行状态字及其变位标志"
// #define STR_AFN_0C_F29  "F29  当前铜损、铁损有功总电能示值"
// #define STR_AFN_0C_F30  "F30  上一结算日当前铜损、铁损有功总电能示值"
// #define STR_AFN_0C_F31  "F31  当前A、B、C三相正/反向有功电能示值、组合无功1/2电能示值"
// #define STR_AFN_0C_F32  "F32  上一结算日A、B、C三相正/反向有功电能示值、组合无功1/2电能示值"
// 
// //5
// #define STR_AFN_0C_F33  "F33  当前正向有/无功(组合无功1)电能示值、一/四象限无功电能示值"
// #define STR_AFN_0C_F34  "F34  当前反向有/无功(组合无功2)电能示值、二/三象限无功电能示值"
// #define STR_AFN_0C_F35  "F35  当月正向有/无功最大需量及发生时间"
// #define STR_AFN_0C_F36  "F36  当月反向有/无功最大需量及发生时间"
// #define STR_AFN_0C_F37  "F37  上月(上一结算日)正向有/无功(组合无功1)电能示值、一/四象限无功电能示值"
// #define STR_AFN_0C_F38  "F38  上月(上一结算日)反向有/无功(组合无功2)电能示值、二/三象限无功电能示值"
// #define STR_AFN_0C_F39  "F39  上月（上一结算日）正向有/无功最大需量及发生时间"
// #define STR_AFN_0C_F40  "F40  上月（上一结算日）反向有/无功最大需量及发生时间"
// 
// //6
// #define STR_AFN_0C_F41  "F41  当日正向有功电能量"
// #define STR_AFN_0C_F42  "F42  当日正向无功电能量"
// #define STR_AFN_0C_F43  "F43  当日反向有功电能量"
// #define STR_AFN_0C_F44  "F44  当日反向无功电能量"
// #define STR_AFN_0C_F45  "F45  当月正向有功电能量"
// #define STR_AFN_0C_F46  "F46  当月正向无功电能量"
// #define STR_AFN_0C_F47  "F47  当月反向有功电能量"
// #define STR_AFN_0C_F48  "F48  当月反向无功电能量"
// 
// //7
// #define STR_AFN_0C_F49  "F49  当前电压、电流相位角"
// 
// //8
// 
// #define STR_AFN_0C_F57  "F57  当前A、B、C三相电压、电流2～N次谐波有效值"
// #define STR_AFN_0C_F58  "F58  当前A、B、C三相电压、电流2～N次谐波含有率"
// 
// //9
// #define STR_AFN_0C_F65  "F65  当前电容器投切状态"
// #define STR_AFN_0C_F66  "F66  当前电容器累计补偿投入时间和次数"
// #define STR_AFN_0C_F67  "F67  当日、当月电容器累计补偿的无功电能量"
// 
// //10
// 
// #define STR_AFN_0C_F73  "F73  直流模拟量实时数据"
// //11
// #define STR_AFN_0C_F81  "F81  小时冻结总加有功功率"
// #define STR_AFN_0C_F82  "F82  小时冻结总加无功功率"
// #define STR_AFN_0C_F83  "F83  小时冻结总加有功总电能量"
// #define STR_AFN_0C_F84  "F84  小时冻结总加无功总电能量"
// 
// //12
// #define STR_AFN_0C_F89  "F89  小时冻结有功功率"
// #define STR_AFN_0C_F90  "F90  小时冻结A相有功功率"
// #define STR_AFN_0C_F91  "F91  小时冻结B相有功功率"
// #define STR_AFN_0C_F92  "F92  小时冻结C相有功功率"
// #define STR_AFN_0C_F93  "F93  小时冻结无功功率"
// #define STR_AFN_0C_F94  "F94  小时冻结A相无功功率"
// #define STR_AFN_0C_F95  "F95  小时冻结B相无功功率"
// #define STR_AFN_0C_F96  "F96  小时冻结C相无功功率"
// //13
// #define STR_AFN_0C_F97  "F97  小时冻结A相电压"
// #define STR_AFN_0C_F98  "F98  小时冻结B相电压"
// #define STR_AFN_0C_F99  "F99  小时冻结C相电压"
// #define STR_AFN_0C_F100  "F100  小时冻结A相电流"
// #define STR_AFN_0C_F101  "F101  小时冻结B相电流"
// #define STR_AFN_0C_F102  "F102  小时冻结C相电流"
// #define STR_AFN_0C_F103  "F103  小时冻结零序电流"
// 
// //14
// #define STR_AFN_0C_F105  "F105  小时冻结正向有功总电能量"
// #define STR_AFN_0C_F106  "F106  小时冻结正向无功总电能量"
// #define STR_AFN_0C_F107  "F107  小时冻结反向有功总电能量"
// #define STR_AFN_0C_F108  "F108  小时冻结反向无功总电能量"
// #define STR_AFN_0C_F109  "F109  小时冻结正向有功总电能示值"
// #define STR_AFN_0C_F110  "F110  小时冻结正向无功总电能示值"
// #define STR_AFN_0C_F111  "F111  小时冻结反向有功总电能示值"
// #define STR_AFN_0C_F112  "F112  小时冻结反向无功总电能示值"
// 
// //15
// #define STR_AFN_0C_F113  "F113  小时冻结总功率因数"
// #define STR_AFN_0C_F114  "F114  小时冻结A相功率因数"
// #define STR_AFN_0C_F115  "F115  小时冻结B相功率因数"
// #define STR_AFN_0C_F116  "F116  小时冻结C相功率因数"
// 
// // 16
// #define STR_AFN_0C_F121  "F121  小时冻结直流模拟量"
// 
// //17
// #define STR_AFN_0C_F129  "F129  当前正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F130  "F130  当前正向无功（组合无功1）电能示值（总、费率1～M）"
// #define STR_AFN_0C_F131  "F131  当前反向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F132  "F132  当前反向无功（组合无功1）电能示值（总、费率1～M）"
// #define STR_AFN_0C_F133  "F133  当前一象限无功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F134  "F134  当前二象限无功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F135  "F135  当前三象限无功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F136  "F136  当前四象限无功电能示值（总、费率1～M）"
// //18
// #define STR_AFN_0C_F137  "F137  上月（上一结算日）正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F138  "F138  上月（上一结算日）正向无功（组合无功1）电能示值（总、费率1～M）"
// #define STR_AFN_0C_F139  "F139  上月（上一结算日）反向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F140  "F140  上月（上一结算日）反向无功（组合无功1）电能示值（总、费率1～M）"
// #define STR_AFN_0C_F141  "F141  上月（上一结算日）一象限无功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F142  "F142  上月（上一结算日）二象限无功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F143  "F143  上月（上一结算日）三象限无功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F144  "F144  上月（上一结算日）四象限无功电能示值（总、费率1～M）"
// 
// //19
// #define STR_AFN_0C_F145  "F145  当月正向有功最大需量及发生时间（总、费率1～M）"
// #define STR_AFN_0C_F146  "F146  当月正向无功最大需量及发生时间（总、费率1～M）"
// #define STR_AFN_0C_F147  "F147  当月反向有功最大需量及发生时间（总、费率1～M）"
// #define STR_AFN_0C_F148  "F148  当月反向无功最大需量及发生时间（总、费率1～M）"
// #define STR_AFN_0C_F149  "F149  上月（上一结算日）正向有功最大需量及发生时间（总、费率1～M）"
// #define STR_AFN_0C_F150  "F150  上月（上一结算日）正向无功最大需量及发生时间（总、费率1～M）"
// #define STR_AFN_0C_F151  "F151  上月（上一结算日）反向有功最大需量及发生时间（总、费率1～M）"
// #define STR_AFN_0C_F152  "F152  上月（上一结算日）反向无功最大需量及发生时间（总、费率1～M）"
// //20
// #define STR_AFN_0C_F153  "F153  第一时区冻结正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F154  "F154  第二时区冻结正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F155  "F155  第三时区冻结正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F156  "F156  第四时区冻结正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F157  "F157  第五时区冻结正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F158  "F158  第六时区冻结正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F159  "F159  第七时区冻结正向有功电能示值（总、费率1～M）"
// #define STR_AFN_0C_F160  "F160  第八时区冻结正向有功电能示值（总、费率1～M）"
// //21
// #define STR_AFN_0C_F161  "F161  电能表远程控制通断电状态及记录"
// #define STR_AFN_0C_F165  "F165  电能表开关操作次数及时间"
// #define STR_AFN_0C_F166  "F166  电能表参数修改次数及时间"
// #define STR_AFN_0C_F167  "F167  电能表购、用电信息"
// #define STR_AFN_0C_F168  "F168  电能表结算信息"
// 
// //22
// #define STR_AFN_0C_F169  "F169  集中抄表中继路由信息"
// #define STR_AFN_0C_F170  "F170  集中抄表电表抄读信息"



 //组1   pn: p0/监测终端号
#define STR_CMD_AFN_D_F1_CLOCK                     "F1  日历时钟"
#define STR_CMD_AFN_D_F2_PARA_STATE                "F2  参数状态标志"
#define STR_CMD_AFN_D_F3_EVENT_1                   "F3  重要事件计数器当前值"
#define STR_CMD_AFN_D_F4_EVENT_2                   "F4  一般事件计数器当前值"
#define STR_CMD_AFN_D_F5_EVENT_STATE               "F5  事件状态标志"
#define STR_CMD_AFN_D_F6_POWR_TIMES                "F6  上电次数"   
//组2   pn:p0/监测终端号
#define STR_CMD_AFN_D_F9_STATE                     "F9  状态量及变位标志"
#define STR_CMD_AFN_D_F10_SWITCH                   "F10 控制输出回路开关接入状态量及变位标志"   
//组4   pn:p0/电气测量点号
#define STR_CMD_AFN_D_F25_POWR_HAVE_T              "F25 总有功功率"
#define STR_CMD_AFN_D_F26_POWR_NONE_T              "F26 总无功功率"
#define STR_CMD_AFN_D_F27_FACTR_T                  "F27 总功率因数"
#define STR_CMD_AFN_D_F28_FACTR_A                  "F28 A相功率因素"
#define STR_CMD_AFN_D_F29_FACTR_B                  "F29 B相功率因数"
#define STR_CMD_AFN_D_F30_FACTR_C                  "F30 C相功率因数"    
//组5   pn:p0/电气测量点号
#define STR_CMD_AFN_D_F33_DEMAND                   "F33 需量"
#define STR_CMD_AFN_D_F34_DEMAND_MAX               "F34 日最大需量"
#define STR_CMD_AFN_D_F35_DEMAND_TIME              "F35 日最大需量发生时间"   
 //组6   pn:电气测量点号
#define STR_CMD_AFN_D_F41_POWR_HAVE_A              "F41 A相有功功率"
#define STR_CMD_AFN_D_F42_POWR_HAVE_B              "F42 B相有功功率"
#define STR_CMD_AFN_D_F43_POWR_HAVE_C              "F43 C相有功功率"
#define STR_CMD_AFN_D_F44_POWR_NONE_A              "F44 A相无功功率"
#define STR_CMD_AFN_D_F45_POWR_NONE_B              "F45 B相无功功率"
#define STR_CMD_AFN_D_F46_POWR_NONE_C              "F46 C相无功功率"   
 //组7   pn:电气测量点号
#define STR_CMD_AFN_D_F49_POWR_HAVE_FRTH           "F49 (正向)有功总电能示数"
#define STR_CMD_AFN_D_F50_POWR_HAVE_BACK           "F50 (反向)有功总电能示数"
#define STR_CMD_AFN_D_F51_POWR_NONE_FRTH           "F51 (正向)无功总电能示数"
#define STR_CMD_AFN_D_F52_POWR_NONE_BACK           "F52 (反向)无功总电能示数"   
 //组8 pn:电气测量点号
#define STR_CMD_AFN_D_F57_VOLT_A                   "F57 A相电压"
#define STR_CMD_AFN_D_F58_VOLT_B                   "F58 B相电压"
#define STR_CMD_AFN_D_F59_VOLT_C                   "F59 C相电压"
#define STR_CMD_AFN_D_F60_VANGL_A                  "F60 A相电压相位角"
#define STR_CMD_AFN_D_F61_VANGL_B                  "F61 B相电压相位角"
#define STR_CMD_AFN_D_F62_VANGL_C                  "F62 C相电压相位角"
#define STR_CMD_AFN_D_F63_VOLT_UBL                 "F63 电压不平衡度"
#define STR_CMD_AFN_D_F64_CIRCLE_V                 "F64 周波"    
//组9 pn:电气测量点号
#define STR_CMD_AFN_D_F65_ELEC_A                   "F65 A相电流"
#define STR_CMD_AFN_D_F66_ELEC_B                   "F66 B相电流"
#define STR_CMD_AFN_D_F67_ELEC_C                   "F67 C相电流"
#define STR_CMD_AFN_D_F68_ELEC_M                   "F68 中性线电流"
#define STR_CMD_AFN_D_F69_EANGL_A                  "F69 A相电流相位角"
#define STR_CMD_AFN_D_F70_EANGL_B                  "F70 B相电流相位角"
#define STR_CMD_AFN_D_F71_EANGL_C                  "F71 C相电流相位角"
#define STR_CMD_AFN_D_F72_ELEC_UBL                 "F72 电流不平衡度"   
 //组10 pn:电气测量点号
#define STR_CMD_AFN_D_F73_VDMAX_A                  "F73 日A相电压极大值"
#define STR_CMD_AFN_D_F74_VDMAX_A_TIME             "F74 日A相电压极大值发生时间"
#define STR_CMD_AFN_D_F75_VDMAX_B                  "F75 日B相电压极大值"
#define STR_CMD_AFN_D_F76_VDMAX_B_TIME             "F76 日B相电压极大值发生时间"
#define STR_CMD_AFN_D_F77_VDMAX_C                  "F77 日C相电压极大值"
#define STR_CMD_AFN_D_F78_VDMAX_C_TIME             "F78 日C相电压极大值发生时间"   
 //组11 pn:电气测量点号
#define STR_CMD_AFN_D_F81_IDMAX_A                  "F81 日A相电流极大值"
#define STR_CMD_AFN_D_F82_IDMAX_A_TIME             "F82 日A相电流极大值发生时间"
#define STR_CMD_AFN_D_F83_IDMAX_B                  "F83 日B相电流极大值"
#define STR_CMD_AFN_D_F84_IDMAX_B_TIME             "F84 日B相电流极大值发生时间"
#define STR_CMD_AFN_D_F85_IDMAX_C                  "F85 日C相电流极大值"
#define STR_CMD_AFN_D_F86_IDMAX_C_TIME             "F86 日C相电流极大值发生时间"   
 //组12 pn:电气测量点号
#define STR_CMD_AFN_D_F89_TFW_HAVE                 "F89 总基波有功功率"
#define STR_CMD_AFN_D_F90_TFW_NONE                 "F90 总基波无功功率"
#define STR_CMD_AFN_D_F91_THW_HAVE                 "F91 总谐波有功功率"
#define STR_CMD_AFN_D_F92_THW_NONE                 "F92 总基波无功功率"   
 //组13 pn:电气测量点号
#define STR_CMD_AFN_D_F97_VDPP_TIME_A              "F97 A相电压越上上限日累计时间"
#define STR_CMD_AFN_D_F98_VDPP_TIME_B              "F98 B相电压越上上限日累计时间"
#define STR_CMD_AFN_D_F99_VDPP_TIME_C              "F99 C相电压越上上限日累计时间"
#define STR_CMD_AFN_D_F100_VDNN_TIME_A             "F100 A相电压越下下限日累计时间"
#define STR_CMD_AFN_D_F101_VDNN_TIME_B             "F101 B相电压越下下限日累计时间"
#define STR_CMD_AFN_D_F102_VDNN_TIME_C             "F102 C相电压越下下限日累计时间"  
  //组14 pn:电气测量点号
#define STR_CMD_AFN_D_F105_VMPP_TIME_A             "F105 A相电压越上上限月累计时间"
#define STR_CMD_AFN_D_F106_VMPP_TIME_B             "F106 B相电压越上上限月累计时间"
#define STR_CMD_AFN_D_F107_VMPP_TIME_C             "F107 C相电压越上上限月累计时间"
#define STR_CMD_AFN_D_F108_VMNN_TIME_A             "F108 A相电压越下下限月累计时间"
#define STR_CMD_AFN_D_F109_VMNN_TIME_B             "F109 B相电压越下下限月累计时间"
#define STR_CMD_AFN_D_F110_VMNN_TIME_C             "F110 C相电压越下下限月累计时间"   
 //组15 pn:电气测量点号 (aberrance)"
#define STR_CMD_AFN_D_F113_VABR_TOTL_A             "F113 A相电压总畸变率"
#define STR_CMD_AFN_D_F114_VABR_TOTL_B             "F114 B相电压总畸变率"
#define STR_CMD_AFN_D_F115_VABR_TOTL_C             "F115 C相电压总畸变率"
#define STR_CMD_AFN_D_F116_EABR_TOTL_A             "F116 A相电流总畸变率"
#define STR_CMD_AFN_D_F117_EABR_TOTL_B             "F117 B相电流总畸变率"
#define STR_CMD_AFN_D_F118_EABR_TOTL_C             "F118 C相电流总畸变率"   
 //组16 pn:电气测量点号
#define STR_CMD_AFN_D_F121_VABR_ODD_A              "F121 A相电压奇次畸变率"
#define STR_CMD_AFN_D_F122_VABR_EVN_A              "F122 A相电压偶次畸变率"
#define STR_CMD_AFN_D_F123_VABR_ODD_B              "F123 B相电压奇次畸变率"
#define STR_CMD_AFN_D_F124_VABR_EVN_B              "F124 B相电压偶次畸变率"
#define STR_CMD_AFN_D_F125_VABR_ODD_C              "F125 C相电压奇次畸变率"
#define STR_CMD_AFN_D_F126_VABR_EVN_C              "F126 C相电压偶次畸变率"   
 //组17 pn:电气测量点号
#define STR_CMD_AFN_D_F128_EABR_OOD_A              "F128 A相电流奇次畸变率"
#define STR_CMD_AFN_D_F129_EABR_EVN_A              "F129 A相电流偶次畸变率"
#define STR_CMD_AFN_D_F130_EABR_OOD_B              "F130 B相电流奇次畸变率"
#define STR_CMD_AFN_D_F131_EABR_EVN_B              "F131 B相电流偶次畸变率"
#define STR_CMD_AFN_D_F132_EABR_OOD_C              "F132 C相电流奇次畸变率"
#define STR_CMD_AFN_D_F133_EABR_EVN_C              "F133 C相电流偶次畸变率"  
  //组18 pn:电气测量点号
#define STR_CMD_AFN_D_F137_FLS_SHRT_A              "F137 A相短时闪变"
#define STR_CMD_AFN_D_F138_FLS_SHRT_B              "F138 B相短时闪变"
#define STR_CMD_AFN_D_F139_FLS_SHRT_C              "F139 C相短时闪变"
#define STR_CMD_AFN_D_F140_FLS_LONG_A              "F140 A相长时闪变"
#define STR_CMD_AFN_D_F141_FLS_LONG_B              "F141 B相长时闪变"
#define STR_CMD_AFN_D_F142_FLS_LONG_C              "F142 C相长时闪变"   
 //组19 pn:电气测量点号
#define STR_CMD_AFN_D_F145_HARM_VOLT_A             "F145 A相N次谐波电压"
#define STR_CMD_AFN_D_F146_HARM_VOLT_B             "F146 B相N次谐波电压"
#define STR_CMD_AFN_D_F147_HARM_VOLT_C             "F147 C相N次谐波电压"
#define STR_CMD_AFN_D_F148_HARM_ELEC_A             "F148 A相N次谐波电流"
#define STR_CMD_AFN_D_F149_HARM_ELEC_B             "F149 B相N次谐波电流"
#define STR_CMD_AFN_D_F150_HARM_ELEC_C             "F150 C相N次谐波电流"   
 //组20 pn:电气测量点号
#define STR_CMD_AFN_D_F153_HARM_VINC_A             "F153 A相N次谐波电压含有率"
#define STR_CMD_AFN_D_F154_HARM_VINC_B             "F154 B相N次谐波电压含有率"
#define STR_CMD_AFN_D_F155_HARM_VINC_C             "F155 C相N次谐波电压含有率"
#define STR_CMD_AFN_D_F156_HARM_EINC_A             "F156 A相N次谐波电流含有率"
#define STR_CMD_AFN_D_F157_HARM_EINC_B             "F157 B相N次谐波电流含有率"
#define STR_CMD_AFN_D_F158_HARM_EINC_C             "F158 C相N次谐波电流含有率"   
 //组30 pn:非电气测量点号
#define STR_CMD_AFN_D_F233_NELC_VALUE              "F233 非电气量"


// 请求3类数据
#define STR_AFN_0E_F1   "F1  请求重要事件"
#define STR_AFN_0E_F2   "F2  请求一般事件"
#define STR_AFN_0E_F3   "F3  请求指定事件"

// AFN 0F
#define STR_AFN_0F_F1   "F1  文件传输方式1"

// AFN 10
#define STR_AFN_10_F1   "F1   透明转发"
#define STR_AFN_10_F9   "F9   转发主站直接对终端的抄读数据命令"
#define STR_AFN_10_F10  "F10  转发主站直接对终端的遥控跳闸/允许合闸命令"
#define STR_AFN_10_F11  "F11  转发主站直接对终端的遥控送电命令"




// 单位类型定义
#define FMT_MINUTE "分"
#define FMT_SECOND "秒"
#define FMT_MS_20  "20ms"
#define FMT_TIMES   "次"
#define FMT_BOOL    "布尔值"
#define FMT_PN      "测量点号"
#define FMT_NULL      ""
#define FMT_UINT8      "UINT8"


typedef struct _CHAR2DECIMAL
{
	char c;
	unsigned char bValue;
}CHAR2DECIMAL, *PCHAR2DECIMAL;

const CHAR2DECIMAL c2a[22] = {
	{'0', 0},
	{'1', 1},
	{'2', 2},
	{'3', 3},
	{'4', 4},
	{'5', 5},
	{'6', 6},
	{'7', 7},
	{'8', 8},
	{'9', 9},
	{'a', 10},
	{'A', 10},
	{'b', 11},
	{'B', 11},
	{'c', 12},
	{'C', 12},
	{'d', 13},
	{'D', 13},
	{'e', 14},
	{'E', 14},
	{'f', 15},
	{'F', 15}
};


class CNxConfig  
{
public:
		void initConfig();

private:
	HKEY    m_hRootKey;    // 写入注册的根位置
 	CString m_rootName;  // 主站预配置注册表项名字
	CString m_mstPreName;  // 主站预配置注册表项名字
	CString m_tmlPreName;  // 终端预配置注册表项名字
	CString m_configMst;   // 主站地址 端口号 发包时延，密码等
	CString m_configTml;   // 终端地址 端口号 发包时延  密码等

	
public:
	UINT8 GetIpNum(CString strIp, int index);
	// 地址
	void SetPreAddress(sMcAddress *psAddr, BOOL bMaster, BOOL bReWrite = TRUE); // 设置地址预配消息
	void GetPreAddress(sMcAddress *psAddr, BOOL bMaster = TRUE); // 获取地址预配消息





	// afn00
	void SetPreAfn00F1(sMcAfn00F1 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	void GetPreAfn00F1(sMcAfn00F1 *pData, BOOL bMaster = TRUE);


    // afn 04
	// f1
	BOOL SetPreAfn04F1(sMcAfn04f1 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F1(sMcAfn04f1 *pData, BOOL bMaster = TRUE);
	// f2
	BOOL SetPreAfn04F2(sMcAfn04f2 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F2(sMcAfn04f2 *pData, BOOL bMaster = TRUE);


	
	// F3
	BOOL SetPreAfn04F3(sMcAfn04f3 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F3(sMcAfn04f3 *pData, BOOL bMaster = TRUE);

	// F4
	BOOL SetPreAfn04F4(sMcAfn04f4 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F4(sMcAfn04f4 *pData, BOOL bMaster = TRUE);
	
	// F5
	BOOL SetPreAfn04F5(sMcAfn04f5 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F5(sMcAfn04f5 *pData, BOOL bMaster = TRUE);
	
	// F6
	BOOL SetPreAfn04F6(sMcAfn04f6 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F6(sMcAfn04f6 *pData, BOOL bMaster = TRUE);

	// F7
	BOOL SetPreAfn04F7(sMcAfn04f7 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F7(sMcAfn04f7 *pData, BOOL bMaster = TRUE);
	
	// F9
	BOOL SetPreAfn04F9(sMcAfn04f9 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F9(sMcAfn04f9 *pData, BOOL bMaster = TRUE);

	// F10
	BOOL SetPreAfn04F10(sMcAfn04f10 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F10(sMcAfn04f10 *pData, BOOL bMaster = TRUE);

	// F17
	BOOL SetPreAfn04F17(sMcAfn04f17 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F17(sMcAfn04f17 *pData, BOOL bMaster = TRUE);

	// f25
	BOOL SetPreAfn04F25(sMcAfn04f25 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F25(sMcAfn04f25 *pData, BOOL bMaster = TRUE);

	// f26
	BOOL SetPreAfn04F26(sMcAfn04f26 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F26(sMcAfn04f26 *pData, BOOL bMaster = TRUE);

	// f27
	BOOL SetPreAfn04F27(sMcAfn04f27 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F27(sMcAfn04f27 *pData, BOOL bMaster = TRUE);

	// f28
	BOOL SetPreAfn04F28(sMcAfn04F28 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F28(sMcAfn04F28 *pData, BOOL bMaster = TRUE);

	// f29
	BOOL SetPreAfn04F29(sMcAfn04F29 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F29(sMcAfn04F29 *pData, BOOL bMaster = TRUE);

	// f30
	BOOL SetPreAfn04F30(sMcAfn04f30 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F30(sMcAfn04f30 *pData, BOOL bMaster = TRUE);

	// f33
	BOOL SetPreAfn04F33(sMcAfn04f33 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F33(sMcAfn04f33 *pData,  BOOL bMaster = TRUE);
	
	// f25 33通用
	BOOL SetPreAfn04F25_f33(CString strKeyName, sMcAfn04f25 *pData,  BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F25_f33(CString strKeyName, sMcAfn04f25 *pData,  BOOL bMaster = TRUE);
	void trans_zigbee(bool strtobuf, CString &strZigbee, char*bufZigbee);
	// f34
	BOOL SetPreAfn04F34(sMcAfn04f34 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F34(sMcAfn04f34 *pData, BOOL bMaster = TRUE);

	// f34
	BOOL SetPreAfn04F35(sMcAfn04f35 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F35(sMcAfn04f35 *pData, BOOL bMaster = TRUE);


	// f49
	BOOL SetPreAfn04F49(sMcAfn04f49 *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn04F49(sMcAfn04f49 *pData, BOOL bMaster = TRUE);

	// afn 0af2
	BOOL SetPreAfn0aF2q(sMcAfn11f2q *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn0aF2q(sMcAfn11f2q *pData, BOOL bMaster = TRUE);

	// afn 0af7
	BOOL SetPreAfn0aF7q(sMcAfn10f7q *pData, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn0aF7q(sMcAfn10f7q *pData, BOOL bMaster = TRUE);

	// afn 0d
	BOOL SetPreAfn0DFS(CString *pData, eMcmd eCmd, BOOL bMaster, BOOL bReWrite = TRUE);
	BOOL GetPreAfn0DFS(CString *pData, eMcmd eCmd, BOOL bMaster = TRUE);


	// pw
	void SetPrePw(CString pw, BOOL bMaster = TRUE);
	void GetPrePw(CString *pw, BOOL bMaster = TRUE);
	void SetMstPreAfn04F1(sMtAfn04F1 *psCfg, BOOL bReWrite = TRUE);
	void GetMstPreAfn04F1(sMtAfn04F1 *psCfg);
	void SetTmlPreAfn04F1(sMtAfn04F1 *psCfg, BOOL bReWrite = TRUE);
	void GetTmlPreAfn04F1(sMtAfn04F1 *psCfg);
	void SetPrePn(eMtCmd eCmd, eMtRole eRole,UINT16 *pusPN, UINT8 ucNum, BOOL bReWrite = TRUE);
		void SetPrePn31(eMcmd eCmd, eMcRole eRole,UINT16 *pusPN, UINT8 ucNum, BOOL bReWrite = TRUE);

	void GetPrePn(eMtCmd eCmd, eMtRole eRole,UINT16 *pusPN, UINT8 *pucNum);
	void GetPrePn31(eMcmd eCmd,  eMcRole eRole,UINT16 *pusPN, UINT8 *pucNum);

	void SetPrePnStr(eMtCmd eCmd, eMtRole eRole,CString strValue, BOOL bReWrite = TRUE);
	void SetPrePnStr31(eMcmd eCmd, eMcRole eRole,CString strValue, BOOL bReWrite = TRUE);

	void GetPrePnStr(eMtCmd eCmd, eMtRole eRole,CString *pStr);
	void GetPrePnStr31(eMcmd eCmd, eMcRole eRole,CString *pStr);



	

	unsigned char GetCharValue(char cAscii);
	//get hex string
	void ConverToHexString(char *strHexData, const char* pszSrc, int nLen);
	int HexStringToString(unsigned char* strDest, int nDestLen, const char* pszHexSrc);


	CNxConfig();
	virtual ~CNxConfig();
	


private:


};

#endif // !defined(AFX_NXCONFIG_H__1DD12D49_5364_4329_A836_16957971D23E__INCLUDED_)
