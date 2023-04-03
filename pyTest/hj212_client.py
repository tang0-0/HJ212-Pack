from glob import glob
from pickle import TRUE
import time
import socket

ST = "77"
CN = "2011"
PW = "123456"
MN = "MN1234567890ABCD"
FLAG = "4"
TCP_IP = "127.0.0.1"
TCP_PORT = 30024
TCP_KEEPALIVE = 60
TCP_UPLOAD_PERIOD = 60

DATA_LIST = ["Iae1", "Iae2", "Iae3", "FIg1", "FIg2", "FIg3"]
VALUE = 0


def get_qn():
    timestamp = time.time()
    local_time = time.localtime(timestamp)
    data_head = time.strftime("%Y%m%d%H%M%S", local_time)
    data_secs = (timestamp - int(timestamp)) * 1000
    dt_ms = "%s%03d" % (data_head, data_secs)
    return dt_ms


def get_datetime():
    timestamp = time.time()
    local_time = time.localtime(timestamp)
    str_time = time.strftime("%Y%m%d%H%M%S", local_time)
    return str_time


def encode_header():
    qn = "QN=" + get_qn()
    packet = qn + ";"
    st = "ST=" + ST
    packet = packet + st + ";"
    cn = "CN=" + CN
    packet = packet + cn + ";"
    pw = "PW=" + PW
    packet = packet + pw + ";"
    mn = "MN=" + MN
    packet = packet + mn + ";"
    flag = "Flag=" + FLAG
    packet = packet + flag + ";"
    cp = "CP=&&"
    packet = packet + cp
    return packet


def crc16(text):
    data = bytearray(text, encoding='utf-8')
    crc = 0xffff
    dxs = 0xa001
    for i in range(len(data)):
        hibyte = crc >> 8
        crc = hibyte ^ data[i]
        for j in range(8):
            sbit = crc & 0x0001
            crc = crc >> 1
            if sbit == 1:
                crc ^= dxs
    return hex(crc)[2:].zfill(4).upper()


def hj212_encode():
    header_packet = encode_header()
    datatime = "DataTime=" + get_datetime() + ";"
    data_packet = datatime
    for data in DATA_LIST:
        data_line = data + "-Rtd=" + str(VALUE) + ","
        data_line = data_line + data + "-Flag=N;"
        data_packet += data_line
    data_packet = data_packet.strip(';') + "&&"
    total_data = header_packet + data_packet
    data_crc = crc16(total_data)
    data_len = str(len(total_data) + 6).zfill(4)
    packet = "##" + data_len + total_data + data_crc + "\r\n"
    print(packet)
    return packet


def value_change():
    global VALUE
    print("VALUE = %d" % VALUE)
    VALUE = VALUE + 1
    if VALUE > 100:
        VALUE = 0


def tcp_connect():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    tcp_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE,TCP_KEEPALIVE)
    tcp_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 10)
    tcp_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 3)
    tcp_socket.connect((TCP_IP, TCP_PORT))
    print(tcp_socket)
    return tcp_socket


def tcp_disconnect(socket):
    socket.close()


if __name__ == '__main__':
    with tcp_connect() as sock:
        while TRUE:
            pack = hj212_encode()
            sock.send(pack.encode("utf8"))
            value_change()
            time.sleep(TCP_UPLOAD_PERIOD)
