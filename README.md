## 1. BST, Queue, Heap을 이용한 질병 관리 프로그램
본 프로젝트에서는 BST, Queue, Heap 을 이용해 질병 관리 프로그램을 구현한다 본 프로그램은 Patient_Queue, Location_BST, Patient_BST, Location_MaxHeap 을 가진다
질병 의심 대상 환자 데이터로부터 이름 체온 기침 여부 지역을 입력 받아 이를 Patient_Queue 에 구축하며 Patient_Queue 로부터 pop 된 환자 데이터는 지역 정보를 담고
있는 Location_BST 와 연결된 Patient_BST 에 삽입된다 이 때 Patient_BSTNode 에서는 환자 이름과 질병 의 양음성 여부를 저장한다 BST 에서 pop 명령어를 실행하면
Location_MaxHeap 구조로 데이터가 pop 되며 힙의 각 노드는 지역에 해당하는 환자 수를 기준으로 정렬된다.

#### 구조
- Patient_Queue : data.txt로부터 데이터를 불러와 환자 이름 체온 기침여부 , 지역이 저장된 PatientNode 로 이루어진 Queue 를 구축한다 Queue 의 구현에는 <queue> 라이브러리의 STL 을 이용한다
- Location_BST : Patient_Queue 에서 방출된 노드의 지역 정보를 확인하여 해당 LocationNode 에 연결된 Patient_BST 에 삽입한다 
  <img src = "https://user-images.githubusercontent.com/73420533/166444452-2806f740-020e-485b-a6a5-b59c9447afae.png"  width="40%" height="40%"></img> 
- Patient_BST : 각 Location_BST 는 Patient _BST 를 갖는다 Location_BST 는 Patient_BST 의 root 노드의 주소 값을 저장하는 방식으로 연결된다. Patient_Queue에서 방출된 데이터는 LocatioBSTNode 의 타입으로 Patient_BST 를 사전순으
로 구축하며 저장되며 각 노드는 이름과 양음성 여부를 저장한다 체온 37.5 도 이상과 기침 여부 Y 가 만족할 때를 양성으로 판단하여 기호로 표기한다. Patient_BST에서는 Insert, Delete, Print(PRE, IN, POST, LEVEL Ord er) 의 연산을 수행할 수 있
다 노드를 제거할 때 양쪽 자식 노드가 모두 존재하는 경우 왼쪽 자식 노드 중 가장 큰 노드를 제거되는 노드 위치로 변경하는 원칙을 따른다.
- Location_MaxHeap : BST에서 pop 된 데이터가 삽입되는 Heap 으로 각 지역의 노드 환자 수를 count 하여 환자 수 기준으로 정렬된다 BST 에서 방출 연산이 일어나면 Heap 을 재정렬하며 삽입 연산과
Print 기능만 수행한다.
  
#### 기능
- LOAD: txt 파일로부터 정보를 읽어 Patient_Queue 에 저장한다
- ADD: Patient_Queue에 직접 노드를 추가하는 기능을 한다 4 개의 인자를 모두 입력해야만 작동한다.
- QPOP: Patient_Queue의 환자 데이터를 BST 노드로 옮기는 명령어로 첫 번째 인자의 숫자 만큼 Queue 의 front 부터 데이터가 pop 된다.
- SEARCH: 환자의 이름을 인자로 입력받아 BST 에 저장된 환자 정보를 찾아 이름 양성여부를 출력한다.
- PRINT: 자료구조 속 데이터를 출력하는 명령어로 첫 번째 인자로 B 를 입력 시 Patient_BST 에 있는 모든 환자 정보를 출력한다 Pre, in, post, level order 의 네가지 트리 순
회 방법을 따른다 첫 번째 인자로 H 를 입력시 Location_MaxHeap 에 저장된 지역 노드를 level order 로 출력한다.
- BPOP: BST에 저장된 데이터를 Location_MaxHeap 으로 pop 하는 명령어로 BST 에 저장된 노드는 삭제되며 인자로는 환자 이름을 입력받는다.



## 2. Fp Grwoth Tree 를 이용한 상품 추천 프로그램
장바구니 데이터를 입력받아 같이 구매한 상품을 기준으로 Fp Growth 를 구축한다. 상품 구입의 연관성을 Tree 구조로 저장하고 있는 Fp Tree, 상품별 빈도수 및 정보 , 상품과 연
결된 Fp Tree 의 상품 노드를 관리하는 Header Table 가 Fp grwoth 를 구성한다.
  <img src = "https://user-images.githubusercontent.com/73420533/166445541-0c8782ff-1713-4f9c-a24e-33dcdca4a1ef.png"  width="70%" height="70%"></img> 

#### 구조
- FP Growth : market.txt 에 저장된 데이터를 한 줄 단위로 불러와 상품 구입의 연관성을 저장한다. 
FP Tree 는 FPNode 클래스를 통해 Header Table 은 Header Table 클래스를 통해 구현한다.
- Header Table : Index Table과 Data Table 로 나누어 구성한다 Threshold 보다 작은 상품도 포함하여 모든 상품의 정보를 저장하며 Index Table 은 빈도수와 상품명이 list 로 저장된 변수 , DataTable 은
상품명 string 과 상품과 연결되는 노드가 map 으로 저장된 변수이다 해당 노드에는 상품의 정보 및 FP Tree 로 연결되는 포인터를 갖고 있다.

  <img src = "https://user-images.githubusercontent.com/73420533/166445788-85a0e1bc-0fc1-47f9-8412-0cee025e2be5.png"  width="40%" height="40%"></img> 
- FpTree : 자식 노드들은 map 형태로 저장하며 , key 는 string 은 상품명을 저장하고 value 의 FPNode* 는 해당 상품의 빈도수 정보 및 연결된 Node 정보를 저장한다 FP Tree 의 노드는
Header Table 에서 같은 상품의 노드에 연결되어야 한다. FP Tree 에 연결되는 상품 순서는 빈도수 기존으로 내림차순으로 결정이 되며 저장되는 데이터 상품명과 노드이며 상품 노드에는 빈도수 , 부모 노드 포인터 자식 노드 포인트가
저장된다.

  <img src = "https://user-images.githubusercontent.com/73420533/166445926-7149e505-95c5-4b2b-a282-d71133951f93.png"  width="40%" height="40%"></img> 
  
  
  
## 3. 그래프를 통한 최단 경로 탐색 프로그램
방향성과 가중치를 갖고 있는 Matrix 형태의 상점 거리 데이터 파일을 바탕으로 그래프를 생성하여 해당 그래프를 통한 최단 경로 탐색 을 시행하는 프로그램을 작성한다. 그래프 생성 후 각 라빈카프 알고리즘을 통해 상점명과 상점의 주인명의 문자를 비교해 일부 조건에 따라 그래프 가중치의 값을 변경 하고 이후 최소 비용 경로를 BFS, 다익스트라 벨만포드 플로이드 알고리즘을 통해 도출한다. 해당 프로그램은 최단 경로 및 그 최단거리 의 key 값과 정렬 다섯 종류 중 설정 된 key 값 경로 상점의 압축된 문자열을 출력한
다. Weight 가 음수일 경우 다익스트라는 에러를 출력 벨만포드 에서는 음수 사이클이 발생할 경우 에러를 출력하고 그렇지 않을 경우 결과를 출력한다.

  <img src = "https://user-images.githubusercontent.com/73420533/166446189-79ffa069-3c31-4e79-8d84-f44941f6c80c.png"  width="30%" height="30%"></img> 


#### 구조 및 기능
- ##### 가게 정보 데이터 Linked List 로 인접 리스트 생성 
방향성 및 가중치를 갖고 있는 그래프 정보 데이터를 읽어 가게 간 거리 데이터를 Linked List 의 형태로 생성한다 거리 데이터의 첫 줄은 상점의 개수가 , 이후 행과 열에 각
각 Edge 의 Start Vertex 와 End Vertex 의 Weight 를 의미한다 각 행의 문자열은 상점의 이름이다. Graph Class 로 인접 리스트를 Vertex 와 Edge Class 를 이용하여 인접 리스트 내
Vertex(Start Vertex 의 key) 와 Edge(end Vertex 의 key, 가중치 를 구현하며 해당 맵 데이터를 순차적으로 읽어 Linked List 의 가장 끝에 연결하여 Vertex 오름차순으로 저장한다.
 
 <img src = "https://user-images.githubusercontent.com/73420533/166446603-e7baec08-3cda-4aa3-8743-8df76c0392a2.png"  width="40%" height="40%"></img> 

- ##### 가중치 Update :
그래프 최단경로 탐색 전 형성된 그래프 내 거리 가중치 정보를 라빈카프 알고리즘을 통한 문자열 비교를 통해 다음과 같은 규칙에 의해 수정한다.
1. 상점 가게 주인의 이름이 5 글자 이상 동일한 가게는 간선 비용이 10 % 감소 소수점 올림
2. 상점 가게 주인의 이름이 10 글자 이상 동일한 가게는 1 의 규칙 적용 후 간선 비용이 10% 추가 감소 소수점 올림
3. 가게 이름이 한 단어 이상 같은 가게는 간선 비용이 20% 감소 소수점 올림

- ##### 그래프 연산
- BFS : Start Vertex 와 End Vertex 를 입력 받아 큐를 통한 BFS 탐색을 통해 가중치를 고려하지 않은 최단 경로와 가중치를 고려한 거리를 도출한다
- DIJKSTRA : Start Vertex와 End Vertex 를 입력 받아 set 을 통한 DIJKSTRA 탐색을 통해 가중치를 고려한 최단 경로와 거리를 도출한다
- DIJSTRAMIN : Start Vertex 와 End Vertex 를 입력 받아 min Heap 을 통한 DIJKSTRA 탐색을 통해 가중치를 고려한 최단 경로와 거리를 도출한다
- BELLMANFORD : Start Vertex 와 End Vertex 를 입력 받아 벨만 포드 탐색을 통해 가중치를 고려한 최단 경로와 거리를 도출한다 음수인 가중치가 있는 경우에도 사용 가능하며 음수 사이클이 발생한 경우에는 에러를 출력한다
- FLOYD : 입력 인자 없이 모든 쌍에 대하여 최 단 경로 행렬을 도출한다 . 음수인 가중치가 있는 경우에도 사용 가능하며 음수 사이클이 발생한 경우에는 에러를 출력한다.

- ##### 정렬 연산
최단 경로로 방문한 노드를 정렬하여 다시 출력한다. 아래 다섯 종류의 연산이 가능하며 CONFIG 명령어를 통해 어떤 Sort 방식을 사용할 것인지 설정할 수 있다.
- Quick Sort
- Insert Sort
- Merge Sort
- Heap Sort
- Bubble Sort



  
