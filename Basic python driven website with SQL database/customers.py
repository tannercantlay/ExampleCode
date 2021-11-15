import pprint
import mysql.connector
from urlparse import parse_qs
import json

def application(env, start_response):
    start_response('200 OK', [('Content-Type', 'text/html')])
    with open("customers.html", 'r') as customers:
        html = customers.read()
        #checks for the ajax request
    if(env['REQUEST_METHOD'] == 'POST'):
        foo = env['wsgi.input'].read()
        #if the value is not empty
        if foo:
            return query(foo)
    return html.encode()
#function called on request takes integer as parameter
def query(idNumber):

    creds = { 'user' : 'jabba',
              'database' : 'pf',
              'password' : 'Sl4veLe!a',
              'auth_plugin' : 'mysql_native_password'}
    cnx = mysql.connector.connect(**creds)

    cursor = cnx.cursor(dictionary=True)

    #queries mysql server
    cursor.execute('select concat(firstName,\' \',lastName) as name, orders.orderNumber, orders.productCode, products.priceEach, orders.quantity, (products.priceEach*orders.quantity) as total from customers join orders on orders.customerNumber = customers.customerNumber join products on products.productCode = orders.productCode where customers.customerNumber = {} order by orderNumber;'.format(int(idNumber)))


    values = cursor.fetchall()

    dict = []

    #goes through all the values returned by query
    for value in values:

        name = value["name"]
        orderNumber = value['orderNumber']
        productCode = value["productCode"]
        priceEach  = float(value['priceEach'])
        quantityOrdered  = value['quantity']
        total  = float(value['total'])
        #dictionary containing all the values for a certain entry
        temp = {
            "name":name,
            "orderNumber":orderNumber,
            "productCode":productCode,
            "priceEach":priceEach,
            "quantityOrdered":quantityOrdered,
            "total":total
        }
        #appending temp dictionary to the list
        dict.append(temp)

    #converts python list of dictionaries to json file
    jsdict = json.dumps(dict)

    return jsdict
