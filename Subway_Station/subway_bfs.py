# ------------------최단 경로-------------------- #
from collections import deque

station_bfs_graph = { 
    '용산': ['이촌'],
    '이촌': ['서빙고', '동작', '용산'],
    '서빙고': ['이촌', '한남'],
    '한남': ['서빙고', '옥수'],
    '옥수': ['한남', '압구정'],
    '흑석': ['동작'],
    '동작': ['흑석', '구반포', '총신대입구', '이촌'],
    '구반포': ['동작', '신반포'],
    '신반포': ['구반포', '고속터미널'],
    '고속터미널': ['신반포', '잠원', '교대', '내방'],
    '압구정': ['옥수', '신사'],
    '신사': ['압구정', '잠원'],
    '잠원': ['신사', '고속터미널'],
    '총신대입구': ['동작', '내방', '사당'],
    '내방': ['총신대입구', '고속터미널'],
    '사당': ['총신대입구', '방배'],
    '방배': ['사당', '서초'],
    '서초': ['방배', '교대'],
    '교대': ['서초', '고속터미널']
}

def bfs(start, end):
    que = deque([[start]])
    visited = [start]
    while que:
        route = que.popleft()
        node = route[-1]
        
        if node == end:
            return route

        for i in station_bfs_graph.get(node, []):
            if i not in visited:
                visited.append(i)
            else:
                continue
            new_route = list(route)
            new_route.append(i)
            que.append(new_route)