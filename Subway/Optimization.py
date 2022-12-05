'''
환승이 불필요한 경우
- 출발역의 라인과 도착역의 라인이 동일한 경우.

-> 같은 호선에서만 이동 (dfs)

환승이 필요한 경우
- 출발역의 라인과 도착역의 라인이 다른 경우.
- 환승 1번, 2번이상의 경우로 나눔.

1. 환승 1번인 경우
-> 출발 역을 기준으로 투 포인터 적용
-> 포인터를 움직여 환승 역의 라인과 도착 역의 라인이 겹치는 역을 탐색
-> 탐색한 역에서 dfs진행

2. 환승 2번 이상인 경우
1번이 없을 경우는 환승이 최소 2번이상 필요한 상황이다.
(있어도 그게 최단 경로가 아닐 수 있음)
bfs
'''
import Station_Information as si
import Shortest_Route

def transfer(start, end, trans = True):
    
    start_line = si.st_infor.get(start).get('호선')
    end_line = si.st_infor.get(end).get('호선')
    st_line = ''
    
    # 환승이 필요한지 검사 -> True = 필요, False = 불필요
    for line in start_line:
        if line in end_line:
            trans = False
            st_line = line
    
    # 환승이 불필요한 경우
    if not trans:
        return Shortest_Route.shortest_route_dfs(start, end, st_line)
    # 환승이 필요한 경우
    else:
        tr_1 = Shortest_Route.shortest_route_bfs_1(start, end)
        print(tr_1)
        tr_2 = Shortest_Route.shortest_route_bfs_2(start, end)
        print(tr_2)
        shortest_route = min(tr_1, tr_2, key=len)
        return shortest_route

print(transfer('흑석', '낙성대'))