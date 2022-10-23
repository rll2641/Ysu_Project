import heapq
import sys
import Subway_Information as si

def shortest_distance_dijk(start):
    
    station_distance = {node: sys.maxsize for node in si.station_information}
    station_distance[start] = 0
    que = []
    heapq.heappush(que, (station_distance[start], start))

    while que:
      distance, node = heapq.heappop(que)
      
      if station_distance[node] < distance:
            continue
          
      for n, d in si.station_information.get(node).get('거리').items():
        min_distance = distance + d
        
        if min_distance < station_distance[n]:
          station_distance[n] = min_distance
          heapq.heappush(que,(min_distance, n))

    return station_distance