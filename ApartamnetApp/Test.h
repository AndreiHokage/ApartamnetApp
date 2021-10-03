#pragma once
class Test
{
private:
	void test_filtrebyspr();
	void test_add_myvector();
	void test_get_all_myvector();
	void test_delete_myvector();
	void test_locatar();
	void test_set_locatar();
	void test_validare_locatar();
	void test_add_repo();
	void test_delete_repo();
	void test_search_repo();
	void test_update_repo();
	void test_add_service();
	void test_delete_service();
	void test_update_service();
	void test_search_service();
	void test_filtrebytype();
	void test_sortbyname();
	void test_sortbyspr();
	void test_sortmp();
	void test_add_list();
	void test_raport_type();
	void test_undo_add();
	void test_undo_delete();
	void test_undo_update();

public:

	Test() = default;
	void run_all_tests();
};

class Test_all :Test
{
private:
	void test_repolab_add();
	void test_repolab_update();
	void test_repolab_delete();
	void test_repolab_search();

public:
	void run_all();
};