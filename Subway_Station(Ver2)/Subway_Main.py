from tkinter import *
from tkinter.font import Font
import tkinter

import Subway_Route as sr
import Subway_Distance as sd
import Subway_Transfer as st
import Subway_Shortest_Transfer as sst

# 타이틀 이름, 크기
subway = Tk()
subway.title("지하철 최단경로")
subway.geometry("1400x900")

# 이미지 불러오기
subway_img = tkinter.PhotoImage(file="지하철.png")
label = tkinter.Label(subway, image=subway_img)
label.place(x=0, y=0)

# 폰트 변경
subway_font = Font(size=18)

# 출발열 입력
input_start = Entry(subway)
input_start.place(x=1050, y=30, width=200, height=50)
input_start.configure(font=subway_font)
def receive_start():
    st = input_start.get()
    
# 출발열 선택 버튼
btn_start = Button(subway, text="출발역 선택")
btn_start.config(width=10, height=2)
btn_start.config(command=receive_start)
btn_start.place(x=1100, y=80)

# 도착역
input_end = Entry(subway)
input_end.place(x=1050, y=150, width=200, height=50)
input_end.configure(font=subway_font)
def receive_end():
    ed = input_end.get()
    
# 도착열 선택 버튼
btn_end = Button(subway, text="도착역 선택")
btn_end.config(width=10, height=2)
btn_end.config(command=receive_end)
btn_end.place(x=1100, y=200)

# 최단 경로 출력
label_bfs = Label(subway)
label_bfs.place(x=950, y=400)
label_transfer = Label(subway)
label_transfer.place(x=950, y=500)
def bfs_start():
    result = sr.shortest_route(input_start.get(), input_end.get())
    label_bfs.configure(text="경로:" + "->".join(result), wraplength=400, font=subway_font)
    transfer_info = st.transfer(result)
    label_transfer.configure(text='환승 정보: ' + '\n'.join(transfer_info), wraplength=400, font=subway_font)
    
# 최단 경로 시작
btn_bfs = Button(subway, text="최단 경로")
btn_bfs.config(width=10, height=2)
btn_bfs.config(command=bfs_start)
btn_bfs.place(x=1070, y=300)

# 최단 거리 출력
label_dijk = Label(subway)
label_dijk.place(x=950, y=600)
label_transfer2 = Label(subway)
label_transfer2.place(x=950, y=700)
def dijk_start():
    result = sst.shortest_transfer(input_start.get(), input_end.get())
    label_dijk.configure(text="경로:" + "->".join(result), wraplength=400 ,font=subway_font)
    transfer_info = st.transfer(result)
    label_transfer2.configure(text='환승 정보: ' + '\n'.join(transfer_info), wraplength=400, font=subway_font)
    
# 최단 거리
btn_dijk = Button(subway, text="최단 환승")
btn_dijk.config(width=10, height=2)
btn_dijk.config(command=dijk_start)
btn_dijk.place(x=1150, y=300)

# 최소 환승
subway.mainloop()