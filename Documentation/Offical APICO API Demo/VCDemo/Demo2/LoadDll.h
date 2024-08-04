// LoadDll.h: interface for the CLoadDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADDLL_H__B8267873_59D6_11D5_B5A0_B42C742B6543__INCLUDED_)
#define AFX_LOADDLL_H__B8267873_59D6_11D5_B5A0_B42C742B6543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
//DLL函数指针类型定义
//控制卡和轴设置函数
typedef int (CALLBACK* LPFNDLL_auto_set)(void);
typedef int (CALLBACK* LPFNDLL_init_board)(void);
typedef int (CALLBACK* LPFNDLL_get_max_axe)(void);
typedef int (CALLBACK* LPFNDLL_get_board_num)(void);
typedef int (CALLBACK* LPFNDLL_get_axe)(int board_no);
typedef int (CALLBACK* LPFNDLL_set_outmode)(int ch,int mode,int logic);
typedef int (CALLBACK* LPFNDLL_set_home_mode)(int ch,int origin_mode);
typedef int (CALLBACK* LPFNDLL_set_maxspeed)(int ch , double speed);
typedef int (CALLBACK* LPFNDLL_set_conspeed)(int ch , double conspeed);
typedef double (CALLBACK* LPFNDLL_get_conspeed)(int ch);
typedef int (CALLBACK* LPFNDLL_set_profile)(int ch , double vl , double vh , double ad,double de);
typedef int (CALLBACK* LPFNDLL_get_profile)(int ch , double *vl , double *vh , double *ad,double *de);
typedef int (CALLBACK* LPFNDLL_set_vector_conspeed)(double conspeed);
typedef int (CALLBACK* LPFNDLL_set_vector_profile)(double vec_vl , double vec_vh ,double vec_ad,double vec_de);
typedef double (CALLBACK* LPFNDLL_get_vector_conspeed)();
typedef int (CALLBACK* LPFNDLL_get_vector_profile)(double *vec_vl , double *vec_vh ,double *vec_ad,double *vec_de);
typedef double (CALLBACK* LPFNDLL_get_rate)(int ch);

//运动指令函数
typedef int (CALLBACK* LPFNDLL_con_pmove)(int ch,long step);
typedef int (CALLBACK* LPFNDLL_fast_pmove)(int ch,long step);
typedef int (CALLBACK* LPFNDLL_con_pmove2)(int ch1,long step1,int ch2,long step2);
typedef int (CALLBACK* LPFNDLL_fast_pmove2)(int ch1,long step1,int ch2,long step2);
typedef int (CALLBACK* LPFNDLL_con_pmove3)(int ch1,long step1,int ch2,long step2,int ch3,long step3);
typedef int (CALLBACK* LPFNDLL_fast_pmove3)(int ch1,long step1,int ch2,long step2,int ch3,long step3);
typedef int (CALLBACK* LPFNDLL_con_pmove4)(int ch1,long step1,int ch2,long step2,int ch3,long step3,int ch4,long step4);
typedef int (CALLBACK* LPFNDLL_fast_pmove4)(int ch1,long step1,int ch2,long step2,int ch3,long step3,int ch4,long step4);
typedef int (CALLBACK* LPFNDLL_con_vmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_fast_vmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_con_vmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_fast_vmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_con_vmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_fast_vmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_con_vmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_fast_vmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_con_hmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_fast_hmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_con_hmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_fast_hmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_con_hmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_fast_hmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_con_hmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_fast_hmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_con_line2)(int ch1,long pos1,int ch2, long pos2);
typedef int (CALLBACK* LPFNDLL_con_line3)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3);
typedef int (CALLBACK* LPFNDLL_con_line4)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3,int ch4,long pos4);
typedef int (CALLBACK* LPFNDLL_fast_line2)(int ch1,long pos1,int ch2, long pos2);
typedef int (CALLBACK* LPFNDLL_fast_line3)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3);
typedef int (CALLBACK* LPFNDLL_fast_line4)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3,int ch4,long pos4);

//20080131,V220
typedef int (CALLBACK* LPFNDLL_change_pos)(int ch, long pos);
typedef int (CALLBACK* LPFNDLL_enable_softlimit)(int ch, int mode);
typedef int (CALLBACK* LPFNDLL_set_softlimit)(int ch, int source, int action);
typedef int (CALLBACK* LPFNDLL_set_softlimit_data)(int ch, double nel, double pel);
typedef int (CALLBACK* LPFNDLL_check_softlimit)(int ch);
//制动函数
typedef void (CALLBACK* LPFNDLL_sudden_stop)(int ch);
typedef void (CALLBACK* LPFNDLL_sudden_stop2)(int ch1,int ch2);
typedef void (CALLBACK* LPFNDLL_sudden_stop3)(int ch1,int ch2,int ch3);
typedef void (CALLBACK* LPFNDLL_sudden_stop4)(int ch1,int ch2,int ch3,int ch4);
typedef void (CALLBACK* LPFNDLL_decel_stop)(int ch);
typedef void (CALLBACK* LPFNDLL_decel_stop2)(int ch1,int ch2);
typedef void (CALLBACK* LPFNDLL_decel_stop3)(int ch1,int ch2,int ch3);
typedef void (CALLBACK* LPFNDLL_decel_stop4)(int ch1,int ch2,int ch3,int ch4);

//位置和状态设置函数
typedef long (CALLBACK* LPFNDLL_set_abs_pos)(int ch,long pos);
typedef int (CALLBACK* LPFNDLL_reset_pos)(int ch);
typedef int (CALLBACK* LPFNDLL_set_dir)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_enable_alm)(int ch , int flag);
typedef int (CALLBACK* LPFNDLL_enable_card_alm)(int cardno,int flag);
typedef int (CALLBACK* LPFNDLL_enable_el)(int ch,int flag);//flag--1,有效;flag--0,无效
typedef int (CALLBACK* LPFNDLL_enable_org)(int ch,int flag);//flag--1,有效;flag--0,无效
typedef int (CALLBACK* LPFNDLL_set_card_alm_logic)(int cardno ,int mode);;
typedef int (CALLBACK* LPFNDLL_set_el_logic)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_set_org_logic)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_set_alm_logic)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_get_abs_pos)(int ch,long *pos);
typedef long (CALLBACK* LPFNDLL_get_cur_dir)(int ch);

//状态查询函数
typedef int (CALLBACK* LPFNDLL_check_status)(int ch);
typedef int (CALLBACK* LPFNDLL_check_done)(int ch);
typedef int (CALLBACK* LPFNDLL_check_limit)(int ch);
typedef int (CALLBACK* LPFNDLL_check_home)(int ch);
typedef int (CALLBACK* LPFNDLL_check_card_alarm)(int cardno);
typedef int (CALLBACK* LPFNDLL_check_alarm)(int ch);

//I/O口操作函数
typedef int (CALLBACK* LPFNDLL_checkin_byte)(int cardno);
typedef int (CALLBACK* LPFNDLL_checkin_bit)(int cardno,int bitno);
typedef int (CALLBACK* LPFNDLL_outport_bit)(int cardno,int bitno,int status);
typedef int (CALLBACK* LPFNDLL_outport_byte)(int cardno,int bytedata);
typedef int (CALLBACK* LPFNDLL_check_SFR)(int cardno);

//其它函数
typedef int (CALLBACK* LPFNDLL_set_backlash)(int axis,int blash);
typedef int (CALLBACK* LPFNDLL_start_backlash)(int axis);
typedef int (CALLBACK* LPFNDLL_end_backlash)(int axis);
typedef int (CALLBACK* LPFNDLL_get_lib_ver)(long* major,long *minor1,long *minor2);
typedef int (CALLBACK* LPFNDLL_get_sys_ver)(long* major,long *minor1,long *minor2);
typedef int (CALLBACK* LPFNDLL_get_card_ver)(long cardno,long *type,long* major,long *minor1,long *minor2);

//SPI存储芯片操作函数
typedef int (CALLBACK* LPFNDLL_write_password_flash)(int cardno, int no, long data,long password);
typedef int (CALLBACK* LPFNDLL_read_password_flash)(int cardno, int no, long *data,long password);
typedef int (CALLBACK* LPFNDLL_clear_password_flash)(int cardno, long password);

typedef int (CALLBACK* LPFNDLL_write_flash)(int cardno,int piece, int no, long data);
typedef int (CALLBACK* LPFNDLL_read_flash)(int cardno,int piece,int no,long *data );
typedef int (CALLBACK* LPFNDLL_clear_flash)(int cardno, int piece);

typedef int (CALLBACK* LPFNDLL_check_IC)(int no);
typedef int (CALLBACK* LPFNDLL_get_last_err)();
typedef int (CALLBACK* LPFNDLL_get_err)(int index,int *data);
typedef int (CALLBACK* LPFNDLL_reset_err)();

//mpc.dll函数封装类
class CLoadDll  
{
public:
	CLoadDll();
	virtual ~CLoadDll();
private:
	HINSTANCE hDLL;
	int LoadDllFun();
public:
	///////////////////////////////////
	//函数指针定义
	//控制卡和轴设置函数
	LPFNDLL_auto_set auto_set;
	LPFNDLL_init_board init_board;
	LPFNDLL_get_max_axe get_max_axe;
	LPFNDLL_get_board_num get_board_num;
	LPFNDLL_get_axe get_axe;
	LPFNDLL_set_outmode set_outmode;
	LPFNDLL_set_home_mode set_home_mode;
	LPFNDLL_set_maxspeed set_maxspeed;
	LPFNDLL_set_conspeed set_conspeed;
	LPFNDLL_get_conspeed get_conspeed;
	LPFNDLL_set_profile set_profile;
	LPFNDLL_get_profile get_profile;
	LPFNDLL_set_vector_conspeed set_vector_conspeed;
	LPFNDLL_set_vector_profile set_vector_profile;
	LPFNDLL_get_vector_conspeed get_vector_conspeed;
	LPFNDLL_get_vector_profile get_vector_profile;
	LPFNDLL_get_rate get_rate;

	//运动函数
	LPFNDLL_con_pmove con_pmove;
	LPFNDLL_fast_pmove fast_pmove;
	LPFNDLL_con_pmove2 con_pmove2;
	LPFNDLL_fast_pmove2 fast_pmove2;
	LPFNDLL_con_pmove3 con_pmove3;
	LPFNDLL_fast_pmove3 fast_pmove3;
	LPFNDLL_con_pmove4 con_pmove4;
	LPFNDLL_fast_pmove4 fast_pmove4;
	LPFNDLL_con_vmove con_vmove;
	LPFNDLL_fast_vmove fast_vmove;
	LPFNDLL_con_vmove2 con_vmove2;
	LPFNDLL_fast_vmove2 fast_vmove2;
	LPFNDLL_con_vmove3 con_vmove3;
	LPFNDLL_fast_vmove3 fast_vmove3;
	LPFNDLL_con_vmove4 con_vmove4;
	LPFNDLL_fast_vmove4 fast_vmove4;
	LPFNDLL_con_hmove con_hmove;
	LPFNDLL_fast_hmove fast_hmove;
	LPFNDLL_con_hmove2 con_hmove2;
	LPFNDLL_fast_hmove2 fast_hmove2;
	LPFNDLL_con_hmove3 con_hmove3;
	LPFNDLL_fast_hmove3 fast_hmove3;
	LPFNDLL_con_hmove4 con_hmove4;
	LPFNDLL_fast_hmove4 fast_hmove4;
	LPFNDLL_con_line2 con_line2;
	LPFNDLL_con_line3 con_line3;
	LPFNDLL_con_line4 con_line4;
	LPFNDLL_fast_line2 fast_line2;
	LPFNDLL_fast_line3 fast_line3;
	LPFNDLL_fast_line4 fast_line4;

	LPFNDLL_change_pos change_pos;
                LPFNDLL_enable_softlimit enable_softlimit;
	LPFNDLL_set_softlimit set_softlimit;
	LPFNDLL_set_softlimit_data set_softlimit_data;
	LPFNDLL_check_softlimit check_softlimit;
	//制动函数
	LPFNDLL_sudden_stop sudden_stop;
	LPFNDLL_sudden_stop2 sudden_stop2;
	LPFNDLL_sudden_stop3 sudden_stop3;
	LPFNDLL_sudden_stop4 sudden_stop4;
	LPFNDLL_decel_stop decel_stop;
	LPFNDLL_decel_stop2 decel_stop2;
	LPFNDLL_decel_stop3 decel_stop3;
	LPFNDLL_decel_stop4 decel_stop4;
	
	//位置和状态设置函数
	LPFNDLL_set_abs_pos set_abs_pos;
	LPFNDLL_reset_pos reset_pos;
	LPFNDLL_set_dir set_dir;
	LPFNDLL_enable_card_alm enable_card_alm;
	LPFNDLL_enable_el enable_el;
	LPFNDLL_enable_org enable_org;
	LPFNDLL_set_card_alm_logic set_card_alm_logic;
	LPFNDLL_set_el_logic set_el_logic;
	LPFNDLL_set_org_logic set_org_logic;
	LPFNDLL_set_alm_logic set_alm_logic;
	LPFNDLL_get_abs_pos get_abs_pos;
	LPFNDLL_get_cur_dir get_cur_dir;

	//状态查询函数
	LPFNDLL_check_status check_status;
	LPFNDLL_check_done check_done;
	LPFNDLL_check_limit check_limit;
	LPFNDLL_check_home check_home;
	LPFNDLL_check_card_alarm check_card_alarm;
	LPFNDLL_check_alarm check_alarm;

	//I/O口操作函数
	LPFNDLL_checkin_byte checkin_byte;
	LPFNDLL_checkin_bit checkin_bit;
	LPFNDLL_outport_bit outport_bit;
	LPFNDLL_outport_byte outport_byte;
	LPFNDLL_check_SFR check_SFR;

	//其它函数
	LPFNDLL_set_backlash set_backlash;
	LPFNDLL_start_backlash start_backlash;
	LPFNDLL_end_backlash end_backlash;
	LPFNDLL_get_lib_ver get_lib_ver;
	LPFNDLL_get_sys_ver get_sys_ver;
	LPFNDLL_get_card_ver get_card_ver;

	LPFNDLL_write_password_flash write_password_flash;
	LPFNDLL_read_password_flash read_password_flash;
	LPFNDLL_clear_password_flash clear_password_flash;
	LPFNDLL_write_flash write_flash;
	LPFNDLL_read_flash read_flash;
	LPFNDLL_clear_flash clear_flash;

	LPFNDLL_check_IC check_IC;
	LPFNDLL_get_last_err get_last_err;
	LPFNDLL_get_err get_err;
	LPFNDLL_reset_err reset_err;

};

#endif // !defined(AFX_LOADDLL_H__B8267873_59D6_11D5_B5A0_B42C742B6543__INCLUDED_)
