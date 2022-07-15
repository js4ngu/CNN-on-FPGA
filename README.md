# CNN-on-FPGA
* Altera DE1-SoC board 환경에서 MNIST Data set을 학습시키고 카메라를 인터페이싱해서 처리해볼 것임
  
## 개발환경
* Altera DE1-SoC board
* Quartus Prime Development Suite (Version 16.0)
  * Qsys system integration tool
  * Nios II Software Build Tools for Eclipse
  * ModelSim starter edition
* Altera Monitor Program (Version 16.0)
# 튜토리얼
## 1. [강의자료](http://www.ecs.umass.edu/ece332/)
   여기에서 Lab0~2까지 따라하면서 카메라 인터페이싱
  *  ### Lab 1-1
  *  [블로그자료](https://jellysong.tistory.com/25) 를 많이 참고하였습니다.
  *  아래 내용은 [강의자료](http://www.ecs.umass.edu/ece332/)와 [블로그자료](https://jellysong.tistory.com/25) 를 잘 조합한것입니다.
  *  [블로그자료](https://jellysong.tistory.com/25) 의 본문을 많이 복붙하였습니다. 양지 바랍니다.
  0. Quartus make project
     1. 프로젝트 경로 : Lab1-1
     2. 프로젝트 명 : Proj_helloworld
     3. 탑모듈 명 : Proj_qsys
        1. 이렇게 해야 나중에 편함
  1. Qsys
     1. IP Catalog 에서 NIOS II Processor, On-Chip Memory, JTAG 항목들을 추가한다.
     2. nios2 는 economy version 선택
  2. Qsys - Connections 
     1. clk_0에서 나오는 clk, clk_reset 을 nios2, onchip, JTAG에 연결
     2. nios2에서 나오는 data_master 을 onchip, JTAG에 연결
     3. nios2에서 나오는 instruction_master 을 onchip에 연결
     4. clk_0에서 나오는 clk_in_reset 을 nios2에 연결 (동영상에서는 마지막에 함)
  3. Qsys - Nios II Processor 설정
     1. Vectors - Reset Vector 을 onchip_memory2_0.s1 으로 설정
     2. Vectors - Exception Vector 을 onchip_memory2_0.s1 으로 설정
  4. Qsys - System
     1. address 중복되는 에러를 방지하기 위해서 수동 설정 혹은 자동 설정
     2. 해당 동영상에서는 System - Base address 사용
     3. proj_qsys 로 저장한다. -> 플젝명이랑 같이 해서 Top모듈 꼬이는거 방지
        1. 이거를 위해서 프로젝트 생성할떄도 탐모듈 proj_qsys로 해줌
     4. Generate 똑같은 이름으로 저장해준다.
  5. Quartus setting
     1. Project Navigator - Files - Add/Remove Files in Project
     2. proj_helloword\proj_qsys\synthesis\proj_qsys.qip 파일을 추가한다.
     3. Compile Design - Analysis & Synthesis 실행
     4. Assignments - Assignment Import에  [Lab1 자료](http://www.ecs.umass.edu/ece332/Labs/Lab1/)의 DE1-SoC Board Settings Import
     5. Assignments - Assignment Editor 에서 clk_clk 를 50Mhz CLOCK [Pin No=PIN_AF14]로 매칭해줌 [DE1-SoC_User_manual Table 3-5참고] : 이거 안하면 PS에 Code가 안올라감...
        * NIOS II – Eclipse – ERROR – ” DownLoad elf failed ” – Verify failed between address ….
        * 이거...
     6.  Comlication
  6. Quartus - Programmer
     1. Auto Detect - Selct 5CSEMA5 
     2. SOCVHPS [ HPS device ] 와 5CSEMA5 [ FPGA device ] 두 개의 Device가 등록된 것을 확인
     3. FPGA device 에서 change file - output_files\proj_qsys.sof 파일을 선택한다.
     4. FPGA device 의 Program/Configure 체크박스에 체크한 후 Start
     5. cdf 파일 저장
  7. NIOS II
     1. Tools - Nios II Software Build Tools for Eclipse
     2. workspace 는 우리가 만든 Project가 있는 폴더를 선택한다. 
     3. Project Explorer - New - Nios II Application and BSP from Template
     4. Target hardware infomation - 우리가 만든 Project 폴더에 proj_qsys.sopcinfo 파일을 선택한다.
     5. 우리는 하나의 프로세서만 가지고 있기에 CPU name 에는 하나만 뜬다. 
     6. Project name : proj_nios, Templates : Hello World Small prints  [Finish]
     7. proj_nois - Build Project // 보드에 .sof 파일이 프로그래밍 되어있다.
  8. 다시한번 Quartus - Programmer ㄱㄱ
  9. NIOS II - RUN
     1.  proj_PS - Run As - Nios II Hardware
     2.  Connctions에 DE-SoC 가 뜨지 않으면 Target Connection - Refresh Connections 클릭
     3.  System ID checks - 두 개의 체크박스 설정
     4.  Apply
     5.  F11 눌러서 디버깅모드로 실행 ㄱㄱ