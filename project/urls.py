from django.urls import path
from .views import *

urlpatterns = [
    path('', main, name='main'),
    path('detail/<int:pk>', detail, name='detail'),
    path('get_distance', get_distance, name='get_distance')
]