# id	file_path	transparent_color_r	g	b
[TEXTURES]
0	resources\simon\simon.png	255	0	255
1	resources\ground\0.png	255	0	255
2	resources\simon\simondeath.png	255	0	255
3	Resources\weapon\morningstar.png	255	0	255
4	Resources\other\burning.png	255	0	255
5	Resources\item\upMor.png	255	0	255
6	Resources\item\heart-lg.png	255	0	255
7	Resources\item\sword.png	255	0	255
8	Resources\enemy\knight_left.png	255	0	255
9	Resources\enemy\knight_right.png	255	0	255
10	Resources\enemy\bat_left.png	255	0	255
11	Resources\enemy\bat_right.png	255	0	255
12	resources\ground\1.png	255	0	255
13	Resources\item\axe.png	255	0	255
14	Resources\item\chicken.png	255	0	255
15	Resources\item\money.png	255	0	255
16	Resources\item\boomerang.png	255	0	255
17	Resources\item\blue.png	255	0	255
18	Resources\item\II.png	255	0	255
19	resources\ground\elevator.png	255	0	255
20	resources\textures\misc.png	176	224	248
21	Resources\weapon\1.png	255	0	255
22	Resources\weapon\2.png	255	0	255
23	Resources\weapon\3.png	255	0	255
24	Resources\weapon\4.png	255	0	255
25	Resources\enemy\hunch_back.png	116	116	116
26	Resources\enemy\ghost.png	255	0	255
27	Resources\enemy\skeleton.png	255	0	255
40	Resources\item\heart-sm.png	255	0	255
41	Resources\other\hit.png	255	0	255
42	Resources\item\money.png	255	0	255
43	Resources\item\money-award.png	255	0	255
100	Resources\extra\blackboard.png	0	0	0
101	Resources\extra\blackboardpause.png	0	0	0

# id	left	top	right	bottom	texture_id
[SPRITES]
# ========================SIMON========================
# idle right
10001	436	202	468	262	0

# walk right
10002	260	201	285	262	0
10003	314	202	344	262	0
10004	378	200	402	262	0

# idle left
10011	12	4	44	63	0

#walk left
10012	196	3	220	63	0
10013	136	4	164	63	0
10014	78	2	102	63	0

# jump left
10016	252	1	284	47	0

# jump right
10017	195	200	228	245	0

# attack left
10018	312	4	360	64	0
10019	373	4	405	64	0
10020	421	6	464	64	0

#attack right
10021	120	202	168	262	0
10022	75	202	107	262	0
10023	16	204	59	262	0

#sitting attack left
10024	432	67	480	113	0
10025	11	133	43	179	0
10026	61	135	105	179	0

#sitting attack right
10027	0	265	48	311	0
10028	437	331	469	377	0
10029	375	333	419	377	0
#Climb UP right
10030	191	266	221	328	0
10031	134	266	158	328	0
#Climb UP left
10032	259	68	289	130	0
10033	322	68	346	130	0
#Climb DOWN right
10034	318	266	350	328	0
10035	266	266	290	328	0
#climb down left
10036	130	68	162	130	0
10037	190	68	214	130	0
#stair down attacking right
10038	302	332	350	394	0
10039	258	332	290	394	0
10040	198	334	239	394	0
#stair down attacking left
10041	130	134	178	196	0
10042	190	134	222	196	0
10043	241	136	282	196	0
#stair up attacking right
10044	120	332	161	394	0
10045	69	332	101	394	0
10046	9	334	53	394	0
#stair up attacking left
10047	319	134	360	196	0
10048	379	134	411	196	0
10049	427	136	471	196	0
# Hurting
10050	438	270	470	328	0

# die 
10099	0	36	64	66	2

#game board
100100	0	0	520	80	100
100101	0	0	900	900	101


#====================BRICK==========================
20001	408	225	424	241	20
20002	0	0	64	16	19

#====================TORCH=========================
3000	0	0	32	64	1
3001	32	0	64	64	1
#===================CANDLE========================
3002	0	0	16	32	12
3003	16	0	32	32	12


#====================WEAPON===========================
#morning star left lv 0
400	23	9	39	57	3
401	69	10	101	48	3
402	143	13	189	29	3
#morningstar right lv 0
403	376	8	392	56	3	
404	314	9	346	47	3
405	226	12	272	28	3
#morning star left lv 1
406	23	77	39	125	3
407	69	78	101	116	3
408	143	87	189	97	3
#morning star right lv 1
409	376	76	392	124	3
410	314	77	346	115	3
411	226	86	272	98	3
#morning star left lv 2
412	23	145	39	193	3
413	69	146	101	184	3
414	111	155	189	167	3
#morning star right lv 2
415	376	144	392	192	3
416	314	145	346	183	3
417	226	154	304	166	3
#======================SWORD=========================
#left
420	0	0	32	18	21
#right
421	0	0	32	18	7
#=====================BLUE===========================
422	0	0	32	26	22
423	32	0	64	26	22
424	64	0	96	26	22
#====================AXE===========================
425	0	0	30	28	23
426	30	0	60	28	23
427	60	0	90	28	23
428	90	0	120	28	23
#====================Boomerang===========================	
429	0	0	28	28	24
430	28	0	56	28	24
431	56	0	84	28	24



#====================EXTRA===========================
#burn for new item

500	18	10	24	36	4
501	58	12	70	36	4
502	98	6	114	36	4

#hit effect

503	0	0	16	20	41
504	16	0	32	20	41

#money award

505	0	0	32	18	43
506	32	0	64	18	43

#======================ITEM========================
#morning Star Upgrade
600	0	0	32	32	5
# Large Heart
601	0	0	24	20	6
# Sword
602	0	0	32	18	7
# Axe
603	0	0	30	28	13
#Chicken
604	0	0	32	26	14
#Boomerang
605	0	0	30	28	16
# Blue
606	0	0	32	32	17
# II
607	0	0	42	42	18
#Small heart
608	0	0	16	16	40
#money
609	0	0	30	30	42
#=====================ENEMY========================
#knight left
700	0	0	32	64	8
701	32	0	64	64	8
702	64	0	96	64	8
703	96	0	128	64	8
#knight right
704	0	0	32	64	9
705	32	0	64	64	9
706	64	0	96	64	9
707	96	0	128	64	9
#Bat left
708	0	0	32	32	10
709	32	0	64	32	10
710	64	0	96	32	10
711	96	0	128	32	10
#Bat right
712	0	0	32	32	11
713	32	0	64	32	11
714	64	0	96	32	11
715	96	0	128	32	11

#Hunch Back left
716	0	0	32	32	25
717	32	0	64	32	25
#Hunch back right
718	64	0	96	32	25
719	96	0	128	32	25

#Skeleton left
720	0	0	34	64	27
721	34	0	68	64	27
722	68	0	102	64	27
723	102	0	136	64	27

		
#Skeleton right
724	136	0	170	64	27
725	170	0	204	64	27
726	204	0	238	64	27
727	238	0	272	64	27

#ghost left
728	0	0	28	28	26
729	28	0	56	28	26
#ghost right
730	56	0	84	28	26
731	84	0	112	28	26

# ani_id	sprite1_id	time1	sprite2_id	time2	...
[ANIMATIONS]

# ==== SIMON =========
#idles right
0	10001	100
#idle left
1	10011	100
#walk right
2	10002	200	10003	200	10004	200
#walk left 
3	10012	200	10013	200	10014	200

#jump left
4	10016	0

#jump right
5	10017	0

#attack left
6	10018	100	10019	100	10020	100
#attack right
7	10021	100	10022	100	10023	100
#sitting left
8	10016	100
#sitting right
9	10017	100

#sitting attack left
10	10024	100	10025	100	10026	100
#sitting attack right
11	10027	100	10028	100	10029	100

#climb up right
12	10030	100	10031	100
#idle on stair up right
13	10030	100
#climb up left
14	10032	100	10033	100
#climb up left Idle
15	10032	100
#climb down right
16	10034	100	10035	100
#climb down right idle
17	10035	100
#climb down right
18	10036	100	10037	100
#climb down right idle
19	10036	100
#up stair attack right
20	10044	100	10045	100	10046	100
#up stair attack left
21	10047	100	10048	100	10049	100
#down stair attack right
22	10038	100	10039	100	10040	100
#down stair attack left
23	10041	100	10042	100	10043	100

#hurting
24	10050	100

#die
25	10099	100

#--------------------------WEAPON--------------------------------
#=============MorningStar===================
#=======LV0========
#left
50	400	100	401	100	402	100
#right	
51	403	100	404	100	405	100
#========LV1=============
#left
52	406	100	407	100	408	100
#right
53	409	100	410	100	411	100

#==========LV2==========
#left
54	412	100	413	100	414	100
#right
55	415	100	416	100	417	100
#=============SWORD==============
#left
56	420	100
#right
57	421	100
#============BLUE=================
58	422	100
59	423	100	424	100
#===========AXE=================
60	425	100	426	100	427	100	428	100
#===========BOOMERANG============
61	429	100	430	100	431	100

#--------------------------END WEAPON--------------------------------
#==================BACKGROUND ITEM ===============

#===============candle==============
301	3002	100	3003	100
#===============torch===================

300	3000	200	3001	200

#===============elevator============

302	20002	100

#==================EXTRA=================
#burning
70	500	150	501	150	502	150
#hit
71	503	150 503 150 503 150
#money award
72	505	150	506	150
#=================ITEMS==================
#Morning Star Upgrade
80	600	100
#lARge Heart
81	601	100
# Sword
82	602	100
#Axe
83	603	100
#Chicken
84	604	100
# Boomerang
85	605	100
# Blue
86	606	100
# II
87	607	100
#small heart
88	608	100
#money
89	609	100


# ======== BRICK ========= START: 6x
999	20001	100

# ========= ENEMY =============

#Knight
#left
90	700	150	701	150	702	150	703	150
#right
91	704	150	705	150	706	150	707	150

#Bat
#stand
92	708	100
#left
93	709	150	710	150	711	150
#right
94	712	150	713	150	714	150

#Hunch back idle left
95	716	100
#Hunch back waking left
96	716	100	717	100
#Hunch back idle right
97	719	100
#Hunch back waking right
98	719	100	718	100
#Skeleton running left
99	720	100	721	100
#Skeleton dying left
100	722	100	723	100
#Skeleton running right
101	727	100	726	100
#Skeleton dying right
102	725	100	724	100
#ghost left
103	728	100	729	100
#ghost right
104	731	100	730	100

#========================================================================================================
#
# id	ani1	ani2	ani3
#
[ANIMATION_SETS]
# SIMON
1	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20	21	22	23	24	25
# BRICK 
2	999
# TORCH
3	300
# MORNINGSTAR
4	50	51	52	53	54	55
# MORNINGSTAR UPGRADE
5	80
#BURNING
6	70	71
# LARGE HEART
7	81
# SWORD
8	82	56	57
# KNIGHT
9	90	91
#BAT
10	92	93	94
#CANDLE
11	301
# AXE
12	83	60	60
# CHICKEN
13	84
# BOOMERANG
14	85	61	61
# BLUE
15	86	58	59
# II
16	87
# Elevator
17	302
# Hunch back
18	95	96	97	98
#Skeleton
19	99  100	101	102
#Ghost
20	103	104
# Small Heart
40	88
#money
41	89	72
#money award
42	72