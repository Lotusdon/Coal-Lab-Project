; Usman Hasan 24K-0759
include irvine32.inc

.data
    think BYTE "Encrypting...",0
    thinkk BYTE "Decrypting...",0
    think2 BYTE "Working Hard ",0
    think3 BYTE "Almost Finished ",0
    tex BYTE "Welcome",0
    box BYTE "Apex Encrypter v1.0",0
    tex2 BYTE "Would you like to encrypt or decrypt ?",0Dh,0Ah,\
              "Yes for Encryption",0Dh,0Ah,\
              "No for Decryption",0
   
    msgEncrypt BYTE "Encrypted String: ",0Dh,0Ah,0Dh,0Ah,\
                     "Would you like to Decrypt this?",0Dh,0Ah,\
                     "Yes to Decrypt",0Dh,0Ah,\
                     "No to Exit",0
   
    msgDecrypt BYTE "Decrypted String: ",0Dh,0Ah,0Dh,0Ah,\
                     "Would you like to Encrypt this?",0Dh,0Ah,\
                     "Yes to Encrypt",0Dh,0Ah,\
                     "No to Exit",0
   
    msg BYTE "Enter your string to encrypt: ",0
    msg2 BYTE "Enter your string to decrypt: ",0
    tex4 BYTE "Decrypted String: ",0
    tex6 BYTE "Encrypted String: ",0
    tex5 BYTE "Original String: ",0
    tex3 BYTE "GoodBye!!",0

    input BYTE 200 dup(0)
    key BYTE ?
    encrypt BYTE 200 dup(?)
   
    resultMsg BYTE 200 dup(0)
    firstRun BYTE 1

    cipher_message db 200 dup(0)


.code

main proc
    call Randomize
    mov eax, 21
    call RandomRange
    add eax, 10
    mov key, al
   
    mov ah,4
    mov al,3
    INVOKE SetTextColor

    mov ebx,OFFSET box
    mov edx,OFFSET tex
    INVOKE MsgBox

mainLoop:
    cmp firstRun, 1
    je firstTime
    jmp notFirstTime

firstTime:
    mov ebx,OFFSET box
    mov edx,OFFSET tex2
    INVOKE MsgBoxAsk
   
    cmp eax,IDYES
    je encryp
   
    cmp eax,IDNO
    je decryp
   
    jmp endd

notFirstTime:
    mov ebx,OFFSET box
    mov edx,OFFSET resultMsg
    INVOKE MsgBoxAsk
   
    cmp eax,IDCANCEL
    je endd
   
    cmp eax,IDNO
    je endd
   
    cmp eax,IDYES
    je continueOperation
   
    jmp endd

continueOperation:
    mov esi, OFFSET encrypt
    mov edi, OFFSET input
    mov ecx, 200
copyLoop:
    mov al, [esi]
    mov [edi], al
    cmp al, 0
    je doneCopy
    inc esi
    inc edi
    loop copyLoop
doneCopy:

    cmp firstRun, 2
    je decryp
    cmp firstRun, 3
    je encryp
    jmp endd

encryp:
    cmp firstRun, 1
    jne skipInput1
   
    Call Clrscr
    mov edx, OFFSET msg
    call WriteString

    mov edx, OFFSET input
    mov ecx, 200
    call ReadString

    cld
    mov esi, offset input
    mov edi, offset cipher_message
    mov ecx, lengthof input
    rep movsb

    pushfd

    invoke str_compare, addr input, addr cipher_message

    popfd

skipInput1:
    Call Clrscr

    mov edx,offset tex5
    Call WriteString
    mov edx,OFFSET input
    Call WriteString
    Call Crlf

    mov eax,2000
    INVOKE Delay

    Call Clrscr

   
    mov edx,OFFSET think
    call WriteString
    call Crlf
    call Spinner
    call Crlf

    Call Clrscr

    mov ecx,SIZEOF input
    mov esi,OFFSET input
    mov edi,OFFSET encrypt

loop1:
    cmp byte ptr [esi],0
    je endloop1
    mov al,[esi]
    xor al,key
    mov [edi],al
    inc edi
    inc esi
    jmp loop1

endloop1:
    mov edx,offset tex6
    Call WriteString
    mov edx,OFFSET encrypt
    Call WriteString
    Call Crlf
    mov eax,2000
    INVOKE Delay
   
    call BuildEncryptMsg
    mov firstRun, 2
    jmp mainLoop

decryp:
    cmp firstRun, 1
    jne skipInput2
   
    Call Clrscr
    mov edx, OFFSET msg2
    call WriteString

    mov edx, OFFSET input
    mov ecx, 200
    call ReadString

skipInput2:
    Call Clrscr

    mov edx,offset tex5
    Call WriteString
    mov edx,OFFSET input
    Call WriteString
    Call Crlf

    mov eax,2000
    INVOKE Delay

    Call Clrscr

   
    mov edx,OFFSET thinkk
    call WriteString
    call Crlf
    call Spinner
    call Crlf

    Call Clrscr

    mov ecx,SIZEOF input
    mov esi,OFFSET input
    mov edi,OFFSET encrypt

loop2:
    cmp byte ptr [esi],0
    je endloop2
    mov al,[esi]
    xor al,key
    mov [edi],al
    inc edi
    inc esi
    jmp loop2

endloop2:
    mov edx,offset tex4
    Call WriteString
    mov edx,OFFSET encrypt
    Call WriteString
    Call Crlf
    mov eax,2000
    INVOKE Delay
   
    call BuildDecryptMsg
    mov firstRun, 3
    jmp mainLoop

endd:
    exit
main endp

BuildEncryptMsg PROC
    mov edi, OFFSET resultMsg
    mov ecx, 200
clearBuffer1:
    mov byte ptr [edi], 0
    inc edi
    loop clearBuffer1
   
    mov edi, OFFSET resultMsg
    mov esi, OFFSET msgEncrypt
copyLabel1:
    mov al, [esi]
    cmp al, 0Dh
    je addResult1
    mov [edi], al
    inc esi
    inc edi
    jmp copyLabel1
   
addResult1:
    mov byte ptr [edi], 0Dh
    inc edi
    mov byte ptr [edi], 0Ah
    inc edi
   
    mov esi, OFFSET encrypt
copyResult1:
    mov al, [esi]
    cmp al, 0
    je addQuestion1
    mov [edi], al
    inc esi
    inc edi
    jmp copyResult1
   
addQuestion1:
    mov byte ptr [edi], 0Dh
    inc edi
    mov byte ptr [edi], 0Ah
    inc edi
    mov byte ptr [edi], 0Dh
    inc edi
    mov byte ptr [edi], 0Ah
    inc edi
   
    mov esi, OFFSET msgEncrypt
    xor ebx, ebx
findQuestion1:
    mov al, [esi]
    cmp al, 0Dh
    jne skipInc1
    inc ebx
    cmp ebx, 2
    je foundQ1
skipInc1:
    inc esi
    jmp findQuestion1
   
foundQ1:
    inc esi
    mov al, [esi]
    cmp al, 0Ah
    jne copyQ1
    inc esi
   
copyQ1:
    mov al, [esi]
    cmp al, 0
    je finishMsg1
    mov [edi], al
    inc esi
    inc edi
    jmp copyQ1
   
finishMsg1:
    mov byte ptr [edi], 0
    ret
BuildEncryptMsg ENDP

BuildDecryptMsg PROC
    mov edi, OFFSET resultMsg
    mov ecx, 200
clearBuffer2:
    mov byte ptr [edi], 0
    inc edi
    loop clearBuffer2
   
    mov edi, OFFSET resultMsg
    mov esi, OFFSET msgDecrypt
copyLabel2:
    mov al, [esi]
    cmp al, 0Dh
    je addResult2
    mov [edi], al
    inc esi
    inc edi
    jmp copyLabel2
   
addResult2:
    mov byte ptr [edi], 0Dh
    inc edi
    mov byte ptr [edi], 0Ah
    inc edi
   
    mov esi, OFFSET encrypt
copyResult2:
    mov al, [esi]
    cmp al, 0
    je addQuestion2
    mov [edi], al
    inc esi
    inc edi
    jmp copyResult2
   
addQuestion2:
    mov byte ptr [edi], 0Dh
    inc edi
    mov byte ptr [edi], 0Ah
    inc edi
    mov byte ptr [edi], 0Dh
    inc edi
    mov byte ptr [edi], 0Ah
    inc edi
   
    mov esi, OFFSET msgDecrypt
    xor ebx, ebx
findQuestion2:
    mov al, [esi]
    cmp al, 0Dh
    jne skipInc2
    inc ebx
    cmp ebx, 2
    je foundQ2
skipInc2:
    inc esi
    jmp findQuestion2
   
foundQ2:
    inc esi
    mov al, [esi]
    cmp al, 0Ah
    jne copyQ2
    inc esi
   
copyQ2:
    mov al, [esi]
    cmp al, 0
    je finishMsg2
    mov [edi], al
    inc esi
    inc edi
    jmp copyQ2
   
finishMsg2:
    mov byte ptr [edi], 0
    ret
BuildDecryptMsg ENDP



Spinner PROC
    mov ecx, 12

SpinLoop:
    mov al, '|'
    call WriteChar
    mov eax, 150
    INVOKE Delay
    mov al, 8
    call WriteChar

    mov al, '/'
    call WriteChar
    mov eax,150
    INVOKE Delay
    mov al, 8
    call WriteChar

    mov al, '-'
    call WriteChar
    mov eax,150
    INVOKE Delay
    mov al, 8
    call WriteChar

    mov al, '\'
    call WriteChar
    mov eax, 150
    INVOKE Delay
    mov al, 8
    call WriteChar

    loop SpinLoop
    ret
Spinner ENDP

end main
