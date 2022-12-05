from collections import deque
import Station_Information as si
from Make_csv import st_line_name as sl

# 환승이 불필요한 경우
def shortest_route_dfs(start, end, st_line):
    st_deque = deque([[start]])
    visited = [start]
    
    while st_deque:
        st_route = st_deque.popleft()
        st_node = st_route[-1]
        
        if st_node == end:
            return st_route
        
        for st in si.st_infor.get(st_node).get('주변역'):
            # 같은 라인에서 역 이동(깊이 탐색)
            if st_line not in si.st_infor.get(st).get('호선'):
                continue
            if st not in visited:
                visited.append(st)
                route = list(st_route)
                route.append(st)
                st_deque.append(route)

# 환승이 필요한 경우, 조건1
def shortest_route_bfs_1(start, end):
    # [1004, 1009]
    st_line_name = {i:j for j, i in sl.items()}
    line_list = si.st_infor.get(start).get('호선')
    line_list = [int(st_line_name.get(line)) for line in line_list]
    
    
    # 호선별 전체역 리스트
    for line in line_list:
        st_list = si.st_df.loc[si.st_df['SUBWAY_ID'] == line]
        st_list = list(st_list['STATN_NM'])
        
        # 투 포인터
        left = st_list.index(start) - 1
        right = st_list.index(start) + 1
        left_visited, right_visited = [start], [start]
        
        while left != -1 or right != len(st_list) - 1:
            
            for line in si.st_infor.get(st_list[left]).get('호선'):
                if line in si.st_infor.get(end).get('호선'):
                    route = shortest_route_dfs(st_list[left], end, line)
                    return left_visited + route

            for line in si.st_infor.get(st_list[right]).get('호선'):
                if line in si.st_infor.get(end).get('호선'):
                    route = shortest_route_dfs(st_list[right], end, line)
                    return right_visited + route
                
            left_visited.append(st_list[left])
            right_visited.append(st_list[right])
            
            left -= 1
            right += 1
            
            if left < 0:
                left = -1
            if right > len(st_list) - 1:
                right = len(st_list) - 1
        
    # 환승 1번의 경우가 없을 경우 -1 리턴
    return -1
                
# 환승이 필요한 경우, 조건2
def shortest_route_bfs_2(start, end):
    st_deque = deque([[start]])
    visited = [start]
    
    while st_deque:
        st_deque = deque([dele for dele in st_deque if len(dele) < 30])
        
        st_route = st_deque.popleft()
        st_node = st_route[-1]
        
        if st_node == end:
            return st_route
        try:
            for st in si.st_infor.get(st_node).get('주변역'):
                if st not in visited:
                    visited.append(st)
                    route = list(st_route)
                    route.append(st)
                    st_deque.append(route)
        except:
            pass
        
# 현재 1, 2 완료 환승2번이상은 임시bfs로 완료