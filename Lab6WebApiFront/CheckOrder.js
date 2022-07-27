window.addEventListener("DOMContentLoaded", () => {
    const queryString = window.location.search;
    const fill = document.querySelector("#fill")
    fill.addEventListener("submit",(event)=> {
        event.preventDefault()
        let objData = {}
        const formData = new FormData(fill)
        let req = ""
        formData.forEach(function (value, key) {
            objData[key] = value
            req += "https://localhost:5001/api/Home/"
        })
        console.log(objData['orderId'])
        console.log(req+ objData['orderId']+"/checkOrder")


        $.get(req+ objData['orderId']+"/checkOrder").done((order) => {
            console.log(order)

            let content = "Заказ не найден"
            if (order.orderId != 0){
                content = '<br><label for="OrderId">' + 'Order Id:  ' + order.id + '</label><br>' +
                    '<label for="Address">Address:  ' + order.address + '</label><br>' +
                    '<label for="GoodQuantity">' + 'Quantity:   ' + order['goodQuantity'] + '</label><br>'+
                '<label for="Sum">' + 'Sum:   ' + order['sum'] + '  UAH' +'</label><br>'+
                    '<label for="Status">' + 'Status:   ' + order.status + '</label><br>'
            }

            document.querySelector("#root").innerHTML += content
        })
    })
})