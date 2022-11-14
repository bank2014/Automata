# Automata

튜링머신 구성
1. CU 2. input 3. memory

memory 없으면 FA  memory가 stack이면 PDA memory 임의 위치에 읽고 쓰면 튜링머신 

메모리 각 cell이 하나의 심볼을 나타낸다  
무한크기의 memory를 가짐  
memory를 tape이라 한다  
M 공식에 blank: 공백 tape 알파벳이 추가된다  
header의 이동방향 L R  
#### 씪(q0, a) = (q1, d, R) : a를 d로 수정 후 이동  

Halt state: 씪이 정의되지않은 configuration일 때 halt된다  
무한루프에 빠지면 halt할 수 없다   

스탠다드 튜링머신   
tape이 양방향으로 제한이 없는(무한한), L R로 움질일 수 있는  
deterministic하다 = 하나의 move만 씪이 정의할 수 있으면  
tape이 곧 아웃풋이다  
input파일이 없다  

move notation: ㅏ  

#### inittal state부터 final까지 도달하는 모든 string들의 집합은 그 오토마타가 accept하는 언어이다  
halt했는데 final state가 아니면 그 string은 튜링머신이 accept하는 언어가 아님 
blank에서 halt하면 aceept한거  

Transducer의 튜링머신  








