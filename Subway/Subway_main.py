import Station_Information as si
import Shortest_Route

def transfer(start, end, trans = True):
    
    start_line = si.st_infor.get(start).get('호선')
    end_line = si.st_infor.get(end).get('호선')
    
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
        # 조건1
        tr_1 = Shortest_Route.shortest_route_dfs_1(start, end)
        # 조건2
        tr_2 = Shortest_Route.shortest_route_dfs_2(start, end)
        # 조건1,2 비교
        shortest_route = min(tr_1, tr_2, key=len)
        # 조건1,2번이 없을 시
        if len(shortest_route) == 50:
            tr_3 = Shortest_Route.shortest_route_bfs_3(start, end)
            return tr_3
        else:
            return shortest_route