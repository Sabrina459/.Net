window.addEventListener("DOMContentLoaded", () => {
    const queryString = window.location.search;
    const urlParams = new URLSearchParams(queryString);
    const req = "https://localhost:5001/api/Home/1?id="+urlParams.get('id')
    $.get(req).done((order) => {
        console.log(order)
        let content = ""
        content +=
            '<label for="OrderId">'+'Order Id:'+order.id+'</label><br><br>' +
            '<label for="Address">Address:</label><br>' +
            '<input type="text" id="Address" name="Address"><br>' +
            '<label for="GoodQuantity">'+'Quantity:'+'</label><br>' +
            '<input type="number" id="GoodQuantity" name="GoodQuantity"><br>'+
            '<input type="submit" value="Make Order">'
        document.querySelector("#fill").innerHTML += content
        const fill = document.querySelector("#fill")
        fill.addEventListener("submit",(event)=>{
            event.preventDefault()
            let objData = {}
            const formData = new FormData(fill)

            formData.forEach(function(value, key) {
                objData[key] = value
            })


            objData['GoodId'] = order['goodId']
            objData['Id'] = order.id
            objData['Status'] = null

            $.post('https://localhost:5001/api/Home', objData).done(function (data){
                let content = ""
                content +='<label>'+data+'</label>'
                document.querySelector("#root").innerHTML += content
            })


            console.log(order)
            console.log(objData)



        })

    })

})