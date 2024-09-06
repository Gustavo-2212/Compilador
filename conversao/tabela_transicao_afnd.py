# Definindo o alfabeto sigma
alfabeto = {chr(i) for i in range(0, 256)}
alfabeto.add("\n")
alfabeto.add("epsilon")

# Criando a tabela com 140 estados, onde cada estado contém dicionários com todas as entradas do alfabeto
tabela_i = {i: {char: set() for char in alfabeto} for i in range(135)}

# Estados Finais
Fi = {7,12,18,22,28,32,38,45,53,58,65,71,78,81,83,85,86,88,89,92,94,96,98,100,103,104,106,108,110,113,114,118,121,124,128,131,134}
Si = {0}
Ti = set(range(0, 135))


# Transições vazias
tabela_i[0]["epsilon"] = {1,8,13,19,23,29,35,39,46,54,59,66,72,79,90,93,95,97,99,101,105,107,109,111,115,119,129,132}


# Token <begin>
tabela_i[1]["b"] = {2}
tabela_i[2]["e"] = {3}
tabela_i[3]["g"] = {4}
tabela_i[4]["i"] = {5}
tabela_i[5]["n"] = {6}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[6][chr(i)] = {7}


# Token <end>
tabela_i[8]["e"] = {9}
tabela_i[9]["n"] = {10}
tabela_i[10]["d"] = {11}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[11][chr(i)] = {12}
    
    
# Token <main>
tabela_i[13]["m"] = {14}
tabela_i[14]["a"] = {15}
tabela_i[15]["i"] = {16}
tabela_i[16]["n"] = {17}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[17][chr(i)] = {18}
    
    
# Token <if>
tabela_i[19]["i"] = {20}
tabela_i[20]["f"] = {21}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[21][chr(i)] = {22}
    

# Token <then>
tabela_i[23]["t"] = {24}
tabela_i[24]["h"] = {25}
tabela_i[25]["e"] = {26}
tabela_i[26]["n"] = {27}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[27][chr(i)] = {28}


# Token <else>
tabela_i[29]["e"] = {30}
tabela_i[30]["l"] = {31}
tabela_i[31]["s"] = {34}
tabela_i[34]["e"] = {33}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[33][chr(i)] = {32}


# Token <do>
tabela_i[35]["d"] = {36}
tabela_i[36]["o"] = {37}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[37][chr(i)] = {38}
        
        
# Token <while>
tabela_i[39]["w"] = {40}
tabela_i[40]["h"] = {41}
tabela_i[41]["i"] = {42}
tabela_i[42]["l"] = {43}
tabela_i[43]["e"] = {44}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[44][chr(i)] = {45}


# Token <repeat>
tabela_i[46]["r"] = {47}
tabela_i[47]["e"] = {48}
tabela_i[48]["p"] = {49}
tabela_i[49]["e"] = {50}
tabela_i[50]["a"] = {51}
tabela_i[51]["t"] = {52}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[52][chr(i)] = {53}


# Token <int>
tabela_i[54]["i"] = {55}
tabela_i[55]["n"] = {56}
tabela_i[56]["t"] = {57}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[57][chr(i)] = {58}


# Token <float>
tabela_i[59]["f"] = {60}
tabela_i[60]["l"] = {61}
tabela_i[61]["o"] = {62}
tabela_i[62]["a"] = {63}
tabela_i[63]["t"] = {64}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[64][chr(i)] = {65}
        
        
# Token <char>
tabela_i[66]["c"] = {67}
tabela_i[67]["h"] = {68}
tabela_i[68]["a"] = {69}
tabela_i[69]["r"] = {70}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[70][chr(i)] = {71}


# Token <until>
tabela_i[72]["u"] = {73}
tabela_i[73]["n"] = {74}
tabela_i[74]["t"] = {77}
tabela_i[77]["i"] = {76}
tabela_i[76]["l"] = {75}
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[75][chr(i)] = {78}
        
        
# Token <oprel>
# ==
tabela_i[79]["="] = {80}
tabela_i[80]["="] = {81}

# !=
tabela_i[79]["!"] = {82}
tabela_i[82]["="] = {83}

# >= e >
tabela_i[79][">"] = {84}
tabela_i[83]["="] = {85}
for i in range(0, 256):
    if chr(i) != "=":
        tabela_i[84][chr(i)] = {86}

# <= e <
tabela_i[79]["<"] = {87}
tabela_i[87]["="] = {88}
for i in range(0, 256):
    if chr(i) != "=":
        tabela_i[87][chr(i)] = {89}


# Token <id>
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_':
        tabela_i[90][chr(i)] = {91}
        
for i in range(0, 256):
    if 'a' <= chr(i) <= 'z' or 'A' <= chr(i) <= 'Z' or chr(i) == '_' or '0' <= chr(i) <= '9':
        tabela_i[91][chr(i)] = {91}
    else:
        tabela_i[91][chr(i)] = {92}


# Token <(>
tabela_i[93]["("] = {94}

# Token <)>
tabela_i[95][")"] = {96}

# Token <;>
tabela_i[97][";"] = {98}

# Token <,>
tabela_i[99][","] = {100}

# Token <:> e <:=>
tabela_i[101][":"] = {102}
for i in range(0, 256):
    if chr(i) != "=":
        tabela_i[102][chr(i)] = {103}
    else:
        tabela_i[102][chr(i)] = {104}


# Token <+>
tabela_i[105]["+"] = {106}

# Token <->
tabela_i[107]["-"] = {108}

# Token </>
tabela_i[109]["/"] = {110}

# Token <*> e <**>
tabela_i[111]["*"] = {112}
for i in range(0, 256):
    if chr(i) != "*":
        tabela_i[112][chr(i)] = {113}
    else:
        tabela_i[112][chr(i)] = {114}
        
        
# Token <const_char>
tabela_i[115]["'"] = {116}
for i in range(0, 256):
    tabela_i[116][chr(i)] = {117}
    
tabela_i[117]["'"] = {118}


# Token <const_num>
for i in range(48, 58):
    tabela_i[119][chr(i)] = {120}
    tabela_i[120][chr(i)] = {120}

tabela_i[120]["E"] = {125}
for i in range(0, 256):
    if '0' <= chr(i) <= '9' or chr(i) == "." or chr(i) == 'E':
        pass
    else:
        tabela_i[120][chr(i)] = {121}
        
tabela_i[120]["."] = {122}

for i in range(48, 58):
    tabela_i[122][chr(i)] = {123}
    tabela_i[123][chr(i)] = {123}
    
for i in range(0, 256):
    if '0' <= chr(i) <= '9' or chr(i) == 'E':
        pass
    else:
        tabela_i[123][chr(i)] = {124}
        
tabela_i[123]["E"] = {125}
tabela_i[125]["+"] = {126}
tabela_i[125]["-"] = {126}
for i in range(48, 58):
    tabela_i[125][chr(i)] = {127}
    tabela_i[126][chr(i)] = {127}
    tabela_i[127][chr(i)] = {127}
    
for i in range(0, 256):
    if '0' <= chr(i) <= '9':
        pass
    else:
        tabela_i[127][chr(i)] = {128}
        
        
# Token <ws>
tabela_i[129][" "] = {130}
tabela_i[129]["\t"] = {130}
tabela_i[129]["\n"] = {130}

tabela_i[130][" "] = {130}
tabela_i[130]["\t"] = {130}
tabela_i[130]["\n"] = {130}

for i in range(0, 256):
    if chr(i) != ' ' and chr(i) != '\t' and chr(i) != '\n':
        tabela_i[130][chr(i)] = {131}
        
        
# Token <comment>
tabela_i[132]["{"] = {133}
for i in range(0, 256):
    if chr(i) != "}":
        tabela_i[133][chr(i)] = {133}
        
tabela_i[133]["}"] = {134}

    


